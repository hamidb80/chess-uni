#pragma once

using System::Drawing::Point;
using namespace System;

enum ChessPieces {
	Empty = 0,

	WhitePawn = 1,
	WhiteRook = 2,
	WhiteKnight = 3,
	WhiteBishop = 4,
	WhiteQueen = 5,
	WhiteKing = 6,

	BlackPawn = -1,
	BlackRook = -2,
	BlackKnight = -3,
	BlackBishop = -4,
	BlackQueen = -5,
	BlackKing = -6,
};

ChessPieces startingPeiceOrder[8][8] = {
	{BlackRook, BlackKnight, BlackBishop, BlackQueen, BlackKing, BlackBishop, BlackKnight, BlackRook},
	{BlackPawn, BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,},

	{Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty,},
	{Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty,},
	{Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty,},
	{Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty,},

	{WhitePawn, WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,},
	{WhiteRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteKing, WhiteBishop, WhiteKnight, WhiteRook},
};

//
//public ref class BoardClass {
//public:
//	cli::array<cli::array<ChessPieces, 8>^, 8>^ board;
//
//	vector<Point> possibleMoves(Point piecePosition);
//	ChessPieces move(Point  lastPiecePosition, Point  newPiecePosition);
//};
