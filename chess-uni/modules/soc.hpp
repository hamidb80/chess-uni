#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <thread>
#include <map>
#include <queue>
#include <iostream>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <json.hpp>
#include <base64.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "../config.h"
#include "../utils/packet.hpp"

using json = nlohmann::json;
using namespace std;

// ----------------------------------------------

class SocketAbs {
protected:
	map<int, DataPacketReciver*> uncompletedRecvs;

	void started_hook() {
		isAlive = true;
	}
	void killed_hook() {
		isAlive = false;
	}
	SOCKET ConnectSocket = INVALID_SOCKET;

public:
	queue<string> eventBus;
	bool isAlive = false;
	//void (*userRecvHandler)(string data);
	//void(*onConnected)() = NULL;
	//void(*onDisconnected)() = NULL;
	//void (*onRecvComplete)(string data);

	virtual void start(string host, string port) {}
	virtual void kill() {}
	virtual void listen() {}

	void simple_send(string what) {
		int res = ::send(ConnectSocket, what.c_str(), what.length(), 0);
		if (res == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			return kill();
		}
	}
	void send(string what) {
		auto bps = DataPacketSender(JSON, what);

		while (!bps.isDone()) {
			this->simple_send(bps.getNextBuffer());
		}
	}
	void sendBeat() {
		auto bps = DataPacketSender(HEARTBEAT, "");
		this->simple_send(bps.getNextBuffer());
	}
	void onRecv(string what) {
		auto bp = new DataPacketReciver(what);

		if (uncompletedRecvs.find(bp->packetId) != uncompletedRecvs.end()) { // if found it in uncompletedRecvs
			uncompletedRecvs[bp->packetId]->append(*bp);
			bp = uncompletedRecvs[bp->packetId];

			if (bp->isDone) { // TODO: remove from uncompletedRecvs
			}
		}
		else if (!bp->isDone) {
			uncompletedRecvs[bp->packetId] = bp;
		}

		if (bp->isDone) {
			eventBus.push(bp->data); // trigger eventHandler
		}
	}
};
class SocketClient : public SocketAbs
{
private:
	struct
		addrinfo* result = NULL,
		* ptr = NULL,
		hints;

public:
	void start(string host, string port) {
		WSADATA wsaData;

		const char* sendbuf = "this is a test";

		int res = WSAStartup(MAKEWORD(2, 2), &wsaData); // Initialize Winsock
		if (res != 0) {
			printf("WSAStartup failed with error: %d\n", res);
			return kill();
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		res = getaddrinfo(host.c_str(), port.c_str(), &hints, &result); // Resolve the server address and port
		if (res != 0) {
			printf("getaddrinfo failed with error: %d\n", res);
			return kill();
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) { // Attempt to connect to an address until one succeeds
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol); // Create a SOCKET for connecting to server
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				return kill();
			}

			res = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen); // Connect to server
			if (res == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}

			break;
		}

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			return kill();
		}

		started_hook();
		new thread(&SocketClient::listen, this);
	}
	void kill() {
		int iResult = shutdown(ConnectSocket, SD_SEND); // shutdown the connection since no more data will be sent
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
		}

		// cleanups
		freeaddrinfo(result);
		closesocket(ConnectSocket);
		WSACleanup();

		killed_hook();
	}
	void listen() {
		while (isAlive) { // Receive until the peer closes the connection
			char recvbuf[DEFAULT_BUFLEN] = { 0 };

			int res = ::recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

			if (res > 0)
				onRecv(string(recvbuf));

			else {
				if (res == 0) printf("Connection closed\n");
				else printf("recv failed with error: %d\n", WSAGetLastError());
				break;
			}
		}
		//kill();
	}
};
class SocketServer : public SocketAbs
{
private:
	SOCKET ListenSocket = INVALID_SOCKET;
	addrinfo* result = NULL;

public:
	void start(string host, string port) {
		WSADATA wsaData;

		struct addrinfo*
			result = NULL,
			hints;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Initialize Winsock 
			printf("WSAStartup failed with error\n");
			return kill();
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(NULL, DEFAULT_PORT, &hints, &result) != 0) { // Resolve the server address and port
			printf("getaddrinfo failed with error\n");
			return kill();
		}

		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); // Create a SOCKET for connecting to server
		if (ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			return kill();
		}

		if (::bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) { // Setup the TCP listening socket
			printf("bind failed with error: %d\n", WSAGetLastError());
			return kill();
		}

		if (::listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) { // trying to bind 
			printf("listen failed with error: %d\n", WSAGetLastError());
			return kill();
		}

		started_hook();
		acceptForFirstClient();

		new thread(&SocketServer::listen, this);
	}
	void acceptForFirstClient() {
		ConnectSocket = accept(ListenSocket, NULL, NULL); // Accept a client socket
		if (ConnectSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			return kill();
		}
	}
	void kill() {
		closesocket(ListenSocket); // No longer need server socket

		int iResult = shutdown(ConnectSocket, SD_SEND); // shutdown the connection since we're done
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
		}

		// cleanups
		freeaddrinfo(result);
		closesocket(ConnectSocket);
		WSACleanup();

		killed_hook();
	}
	void listen() {
		while (isAlive) { // Receive until the peer shuts down the connection
			char recvbuf[DEFAULT_BUFLEN] = { 0 };
			int res = ::recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

			if (res > 0)
				onRecv(recvbuf);

			else {
				if (res == 0)
					printf("Connection closing...\n");
				else
					printf("recv failed with error: %d\n", WSAGetLastError());
				break;
			}
		}
		kill();
	}
};

// ------------------------------------------------

SocketAbs* appSocket = new SocketClient();

using System::Collections::Generic::Dictionary;
using namespace System;
using namespace System::Threading;

delegate void JsonReciever(json);
ref class SocketInterop abstract sealed{
private:
	static Dictionary<String^, JsonReciever^>^ eventMap = gcnew Dictionary<String^, JsonReciever^>();
	static Thread^ eventEmmiterThread;

	static void checkForUpdates() {
		while (true)
		{
			while (!appSocket->eventBus.empty()) {
				auto data = json::parse(appSocket->eventBus.front());
				appSocket->eventBus.pop();

				// TODO catch key "event" does not exists
				trigger(data["event"].get<string>(), data); 
			}

			Thread::Sleep(20);
		}
	}
	static void trigger(string eventName, json data) {
		auto en = gcnew String(eventName.c_str());

		if (eventMap->ContainsKey(en))
			eventMap[en](data);
	}

public:
	static void run() {
		eventEmmiterThread = gcnew Thread(
			gcnew ThreadStart(SocketInterop::checkForUpdates));
		
		eventEmmiterThread->Start();
	}
	
	static void on(string eventName, JsonReciever^ func) {
		auto en = gcnew String(eventName.c_str());
		eventMap[en] = func;
	}
	static void remove(string eventName) {
		auto en = gcnew String(eventName.c_str());
		eventMap->Remove(en);
	}
};