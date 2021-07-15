#pragma once
#include <map>
#include <vector>
#include "gameLogic.h"

using namespace std;

struct MyColor // because Drawing::Color doesn't work
{
	int r, g, b;
	MyColor(int red, int green, int blue) :
		r(red),
		g(green),
		b(blue)
	{}
	MyColor() :
		r(0),
		g(0),
		b(0)
	{}
};

enum BoardBackTheme {
	BlackWhite,
	Wood,
	MagicalMysteryRide,
};
map<BoardBackTheme, string> BoardBackThemeString{
	{BlackWhite, "black & white"},
	{Wood, "wood"},
	{MagicalMysteryRide, "magical mystery ride"},
};
map <BoardBackTheme, vector<MyColor>> BackThemes = {
	{BlackWhite,			{MyColor(238,238,238), MyColor(97,97,97)}      },
	{Wood,					{MyColor(114, 83, 61), MyColor(218, 192, 155)} },
	{MagicalMysteryRide,	{MyColor(124,77, 255), MyColor(209, 196, 233)} }
};

map<ChessPieces, string> peiceFileName = {
	{WhitePawn, "pawn-white.png"},
	{BlackPawn, "pawn-black.png"},

	{WhiteBishop, "bishop-white.png"},
	{BlackBishop, "bishop-black.png"},

	{WhiteKing, "king-white.png"},
	{BlackKing, "king-black.png"},

	{WhiteKnight, "knight-white.png"},
	{BlackKnight, "knight-black.png"},

	{WhiteQueen, "queen-white.png"},
	{BlackQueen, "queen-black.png"},

	{WhiteRook, "rook-white.png"},
	{BlackRook, "rook-black.png"},
};

// http://www.enpassant.dk/chess/fonteng.htm
enum PieciesThemeStyle {
	Solid,
	Curly,
	Pixel,
};
map<PieciesThemeStyle, string> PieciesThemeStyleString = {
	{Solid, "solid"},
	{Curly, "curly"},
	{Pixel, "pixel"},
};

enum PieciesThemeColor {
	Cyan,
	Pink,
};
map<PieciesThemeColor, string> PieciesThemeColorString = {
	{Cyan, "cyan"},
	{Pink, "pink"},
};
