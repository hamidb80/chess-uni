#pragma once

#include "../config.h"
#include "../utils/other.hpp"
#include <string>

using namespace std;

class DataPacket {
protected:
	/// packetId<16> isEnd?<1> data<...rest>
	const int
		chunkHeaderSize = 16 + 1,
		purePacketSize = DEFAULT_BUFLEN - chunkHeaderSize;

public:
	int packetId;
	string data;
};

class DataPacketSender : public DataPacket {
private:
	/// packetId<16> isEnd?<1> data<...rest>
	int lastCursorPosition = 0;

public:
	DataPacketSender(string d)
	{
		packetId = freakin_random_number();
		data = d;
	}

	bool isDone(int plus = 0) {
		return lastCursorPosition + plus >= data.length();
	}
	string getNextBuffer() {
		if (isDone()) throw "is done already";

		string buffer =
			binaryRepr<16>(packetId) +
			binaryRepr<1>(isDone(purePacketSize)) +
			data.substr(lastCursorPosition, purePacketSize);

		lastCursorPosition += purePacketSize;
		return buffer;
	}
};
class DataPacketReciver : public DataPacket {
public:
	bool isDone;

	/// packetId<16> isEnd?<1> data<...rest>
	DataPacketReciver(string currentData) {
		string temp;

		temp = currentData.substr(0, 16);
		packetId = stoi(temp, 0, 2);

		temp = currentData.substr(16, 1);
		isDone = stoi(temp, 0, 2);

		data = currentData.substr(17, purePacketSize);
	}

	void append(DataPacketReciver& another) {
		data.append(another.data);
		isDone = another.isDone;
	}
};
