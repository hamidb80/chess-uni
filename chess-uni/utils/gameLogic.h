#pragma once

using System::Drawing::Point;
using namespace System;
using namespace System::Collections::Generic;

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

bool isBlack(ChessPieces cp) {
	return int(cp) < 0;
}

bool isWhite(ChessPieces cp) {
	return int(cp) > 0;
}

cli::array<ChessPieces, 2>^ newBoard() {
	return gcnew cli::array<ChessPieces, 2>{
		{BlackRook, BlackKnight, BlackBishop, BlackQueen, BlackKing, BlackBishop, BlackKnight, BlackRook},
		{ BlackPawn, BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn,BlackPawn, },

		{ Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty, },
		{ Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty, },
		{ Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty, },
		{ Empty, Empty,Empty,Empty,Empty,Empty,Empty,Empty, },

		{ WhitePawn, WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn,WhitePawn, },
		{ WhiteRook, WhiteKnight, WhiteBishop, WhiteQueen, WhiteKing, WhiteBishop, WhiteKnight, WhiteRook },
	};
}

bool contains(List<Point>^ list, Point point) {
	for (int i = 0; i < list->Count; i++)
		if (list[i] == point)
			return true;

	return false;
}
