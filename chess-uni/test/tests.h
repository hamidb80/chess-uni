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

bool arePointsEqual(Point p1, Point p2)
{
  return (p1.x == p2.x) && (p1.y == p2.y);
}
bool areVectorsEqualAsSets(vector<Point> v1, vector<Point> v2)
{
  if (v1.size() != v2.size())
    return false;

  for (int i = 0; i < v1.size(); i++)
  {
    bool found = false;
    for (int c = 0; c < v1.size(); c++)
      if (arePointsEqual(v1[i], v2[c]))
      {
        found = true;
        break;
      }

    if (found == false)
      return false;
  }
  return true;
}

string to_string(Point p)
{
  string res = "(";
  res += to_string(p.x);
  res += ",";
  res += to_string(p.y);
  res += ")";

  return res;
}
string to_string(vector<Point> v)
{
  string res = "[";
  for (int i = 0; i < v.size(); i++)
    res += to_string(v[i]);

  return res + "]";
}

int main()
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

  {
    int d = bc.possibleMoves(Point(0, 0)).size();
    cout << (d == 0);
  }

  {
    vector<Point>
        expectedMoves = {Point(0, 2)},
        result = bc.possibleMoves(Point(0, 1));

    cout << to_string(expectedMoves) << endl
         << to_string(result) << endl;
    
    cout << areVectorsEqualAsSets(expectedMoves, result);
  }
}

void test(){
	test_BinaryPacketReciever();
}