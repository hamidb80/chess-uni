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

// ---------------------------------------------

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Point
{
public:
    int x, y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

class BoardClass
{
public:
    wstring board[8];

    void setTable(wstring r1, wstring r2, wstring r3, wstring r4,
        wstring r5, wstring r6, wstring r7, wstring r8)
    {
        board[1 - 1] = r1;
        board[2 - 1] = r2;
        board[3 - 1] = r3;
        board[4 - 1] = r4;
        board[5 - 1] = r5;
        board[6 - 1] = r6;
        board[7 - 1] = r7;
        board[8 - 1] = r8;
    }

    vector<Point> possibleMoves(Point piecePosition)
    {
        vector<Point> result;
        return result;
    }
    wchar_t move(Point lastPiecePosition, Point newPiecePosition)
    {
        return L'⛓';
    }
};

int test_ChessBoardClass()
{
    BoardClass bc;
    bc.setTable(
        L"♜♞♝♚♛♝♞♜"s,
        L"♟♟♟♟♟♟♟♟"s,
        L"⛓⛓⛓⛓⛓⛓⛓⛓"s,
        L"⛓⛓⛓⛓⛓⛓⛓⛓"s,
        L"⛓⛓⛓⛓⛓⛓⛓⛓"s,
        L"⛓⛓⛓⛓⛓⛓⛓⛓"s,
        L"♙♙♙♙♙♙♙♙"s,
        L"♖♘♗♕♔♗♘♖"s);

    int d = bc.possibleMoves(Point(0, 0)).size();
    cout << (d == 0);
}


void test() {
	test_BinaryPacketReciever();
}