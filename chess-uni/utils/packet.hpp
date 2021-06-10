#pragma once

#include "../config.h"
#include "../utils/other.hpp"
#include <string>

using namespace std;

enum FileType { HEARTBEAT, JSON };

class DataPacket {
protected:
	/// packetId<16> fileType<1> isEnd?<1> data<...rest>
	const int
		chunkHeaderSize = 16 + 1 + 1,
		purePacketSize = DEFAULT_BUFLEN - chunkHeaderSize;

public:
	FileType fileType;
	int packetId;
	string data;
};
class DataPacketSender : public DataPacket {
private:
	/// packetId<16> fileType<1> isEnd?<1> data<...rest>
	int lastCursorPosition = 0;

public:
	DataPacketSender(FileType ft, string d)
	{
		packetId = freakin_random_number();
		fileType = ft;
		data = d;
	}

	bool isDone(int plus = 0) {
		return lastCursorPosition + plus >= data.length();
	}
	string getNextBuffer() {
		if (isDone()) throw "is done already";

		string buffer =
			binaryRepr<16>(packetId) +
			binaryRepr<1>(fileType) +
			binaryRepr<1>(isDone(purePacketSize)) +
			data.substr(lastCursorPosition, purePacketSize);

		lastCursorPosition += purePacketSize;
		return buffer;
	}
};
class DataPacketReciver : public DataPacket {
public:
	bool isDone;

	/// packetId<16> fileType<1> isEnd?<1> data<...rest>
	DataPacketReciver(string currentData) {
		string temp;

		temp = currentData.substr(0, 16);
		packetId = stoi(temp, 0, 2);

		temp = currentData.substr(16, 1);
		fileType = FileType(stoi(temp, 0, 2));

		temp = currentData.substr(17, 1);
		isDone = stoi(temp, 0, 2);

		data = currentData.substr(18, purePacketSize);
	}

	void append(DataPacketReciver& another) {
		data.append(another.data);
		isDone = another.isDone;
	}
};
