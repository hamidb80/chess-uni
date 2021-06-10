#pragma once
#include "../utils/packet.hpp"

void check(bool pred, string repr = "") {
	if (!pred)
		throw repr;
}

void test_BinaryPacketReciever() {
	//                               packetId<16>    fileType<1> isEnd<1> data<...rest>
	auto b = DataPacketReciver((string)"0000000000000011" + "1" + "0" + "salam");
	check(b.packetId == 3);
	check(b.fileType == JSON);
	check(b.isDone == false);
	check(b.data == "salam");
}

void test() {
	test_BinaryPacketReciever();
}