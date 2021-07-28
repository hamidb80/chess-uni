#pragma once
#include <string>
#include <map>
#include <vector>

#include "../utils/lambda.h"
#include "../utils/gameLogic.h"
#include "../utils/ui.h"

String^ currentDir() {
	return System::AppContext::BaseDirectory;
}

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using System::Collections::Generic::List;
	using DSize = System::Drawing::Size;

	public ref struct ThemeOptions {
		PieciesThemeColor pieciesThemeColor = Pink;
		BoardBackTheme boardBackTheme = MagicalMysteryRide;
		PieciesThemeStyle pieciesThemeStyle = Pixel;
	};

	public ref struct BoardClass {
		cli::array<ChessPieces, 2>^ board = newBoard();
		List<Point>^ dangerPoints = gcnew List<Point>();
		List<Point>^ movePoints = gcnew List<Point>();

		void setBoard(cli::array<ChessPieces, 2>^ newBoard) {
			board = newBoard;
		}

		List<Point>^ possibleMoves(Point piecePosition) {
			auto result = gcnew List<Point>();

			auto piece = board[piecePosition.Y, piecePosition.X];
			bool isWhite = int(piece) > 0;
			bool WhiteCheck = 0;
			bool BlackCheck = 0;
			switch (piece)
			{
			case Empty:
				break;
				///////////////////////////PAWN

			case WhitePawn:

				if (piecePosition.Y - 2 > -1)
				{
					int x = 0, y = 0;
					x = piecePosition.X;
					y = piecePosition.Y;
					if ((x + 1 < 8 && int(board[y - 1, x + 1]) < 0) || (x - 1 > -1 && int(board[y - 1, x - 1]) < 0))
					{
						if (x + 1 < 8 && int(board[y - 1, x + 1]) < 0)
						{
							result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
							if (int(board[y - 1, x]) < 0 || int(board[y - 1, x]) == 0)
							{
								result->Add(Point(piecePosition.X, piecePosition.Y - 1));
							}
						}

						if (x - 1 > -1 && int(board[y - 1, x - 1]) < 0)
						{
							result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
							if (int(board[y - 1, x]) < 0 || int(board[y - 1, x]) == 0)
							{
								result->Add(Point(piecePosition.X, piecePosition.Y - 1));
							}
						}

					}
					
						
					else
					{
						if ((int(board[y - 2, x]) < 0 || int(board[y - 2, x]) == 0) && int(board[y - 1, x]) == 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y - 2));
							result->Add(Point(piecePosition.X, piecePosition.Y - 1));
						}

						else if (int(board[y - 1, x]) < 0 || int(board[y - 2, x]) > 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y - 1));
						}
					}
				

					//else if (int(board[ y - 1 , x]) > 0) {}
				}
				if (piecePosition.Y - 1 > -1)
				{
					int x = 0, y = 0;
					x = piecePosition.X;
					y = piecePosition.Y;
					if (int(board[y - 1, x]) < 0 || int(board[y - 1, x]) == 0)
					{
						result->Add(Point(piecePosition.X, piecePosition.Y - 1));
					}
					if (x + 1 < 8 && int(board[y - 1, x + 1]) < 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
					if (x - 1 > -1 && int(board[y - 1, x - 1]) < 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
					
					else if (int(board[y - 1, x]) < 0 || int(board[y - 2, x]) > 0)
					{
						result->Add(Point(piecePosition.X, piecePosition.Y - 1));
					}

					//else if (int(board[ y - 1 , x]) > 0) {}
				}
				break;
			case BlackPawn:
				//result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				//result->Add(Point(piecePosition.X, piecePosition.Y + 2));
				//////////////////////
				if (piecePosition.Y + 2 < 8)
				{
					int x = 0, y = 0;
					x = piecePosition.X;
					y = piecePosition.Y;
					if (x + 1 < 8 && int(board[y + 1, x + 1]) > 0)
					{
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
						if (int(board[y + 1, x]) > 0 || int(board[y + 1, x]) == 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y + 1));
						}
					}
					if (x - 1 > -1 && int(board[y + 1, x - 1]) > 0)
					{
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
						if (int(board[y + 1, x]) > 0 || int(board[y + 1, x]) == 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y + 1));
						}
					}
					else
					{
						if ((int(board[y + 2, x]) > 0 || int(board[y + 2, x]) == 0) && int(board[y + 1, x]) == 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y + 2));
							result->Add(Point(piecePosition.X, piecePosition.Y + 1));
						}

						else if (int(board[y + 1, x]) > 0 || int(board[y + 2, x]) > 0)
						{
							result->Add(Point(piecePosition.X, piecePosition.Y + 1));
						}
					}
					//else if (int(board[y + 1, x]) < 0) {}
				}
				if (piecePosition.Y + 1 < 8)
				{
					int x = 0, y = 0;
					x = piecePosition.X;
					y = piecePosition.Y;
					
					if (int(board[y + 1, x]) > 0 || int(board[y + 1, x]) == 0)
					{
						result->Add(Point(piecePosition.X, piecePosition.Y + 1));
					}
					if (x + 1 < 8 && int(board[y + 1, x + 1]) > 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
					if (x - 1 > -1 && int(board[y + 1, x - 1]) > 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
					else if (int(board[y + 1, x]) > 0 || int(board[y + 2, x]) > 0)
					{
						result->Add(Point(piecePosition.X, piecePosition.Y + 1));
					}
				}
				


				break;
				////////////////////////////ROOK
			case WhiteRook:
			{
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;
				for (int i = piecePosition.Y + 1; i < 8; i++)
				{
					if (int(board[i, piecePosition.X]) > 0)
						break;
					if (int(board[i, piecePosition.X]) < 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}
					result->Add(Point(piecePosition.X, i));
				}

				for (int i = piecePosition.Y - 1; i > -1; i--)
				{
					if (int(board[i, piecePosition.X]) > 0)
						break;
					if (int(board[i, piecePosition.X]) < 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}

					result->Add(Point(piecePosition.X, i));
				}
				/// ////
				for (int i = piecePosition.X + 1; i < 8; i++)
				{
					if (int(board[piecePosition.Y, i]) > 0)
						break;
					if (int(board[piecePosition.Y, i]) < 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X - 1; i > -1; i--)
				{
					if (int(board[piecePosition.Y, i]) > 0)
						break;
					if (int(board[piecePosition.Y, i]) < 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}

				break;
				

			}
			case BlackRook:
			{
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;

				for (int i = piecePosition.Y + 1; i < 8; i++)
				{
					if (int(board[i, piecePosition.X]) < 0)
						break;
					if (int(board[i, piecePosition.X]) > 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}
					result->Add(Point(piecePosition.X, i));
				}

				for (int i = piecePosition.Y - 1; i > -1; i--)
				{
					if (int(board[i, piecePosition.X]) < 0)
						break;
					if (int(board[i, piecePosition.X]) > 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}

					result->Add(Point(piecePosition.X, i));
				}
				/// ////
				for (int i = piecePosition.X + 1; i < 8; i++)
				{
					if (int(board[piecePosition.Y, i]) < 0)
						break;
					if (int(board[piecePosition.Y, i]) > 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X - 1; i > -1; i--)
				{
					if (int(board[piecePosition.Y, i]) < 0)
						break;
					if (int(board[piecePosition.Y, i]) > 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				break;

			}

			////////////////////////////KNIGHT

			case WhiteKnight:
			{
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;

				if (piecePosition.X + 2 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 2 > -1)
				{

					if (int(board[y + 2, x + 1]) < 0 || int(board[y + 2, x + 1]) == 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));
					if (int(board[y - 2, x + 1]) < 0 || int(board[y - 2, x + 1]) == 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));
					if (int(board[y + 2, x - 1]) < 0 || int(board[y + 2, x - 1]) == 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));
					if (int(board[y - 2, x - 1]) < 0 || int(board[y - 2, x - 1]) == 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (int(board[y + 1, x + 2]) < 0 || int(board[y + 1, x + 2]) == 0)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));
					if (int(board[y - 1, x + 2]) < 0 || int(board[y - 1, x + 2]) == 0)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));
					if (int(board[y + 1, x - 2]) < 0 || int(board[y + 1, x - 2]) == 0)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));
					if (int(board[y - 1, x - 2]) < 0 || int(board[y - 1, x - 2]) == 0)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));
				}
				else
				{


					if (piecePosition.X + 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X + 1 > -1)
						if (int(board[y + 2, x + 1]) < 0 || int(board[y + 2, x + 1]) == 0)
							result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));

					if (piecePosition.X + 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X + 1 > -1)
						if (int(board[y - 2, x + 1]) < 0 || int(board[y - 2, x + 1]) == 0)
							result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));

					if (piecePosition.X - 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X - 1 > -1)
						if (int(board[y + 2, x - 1]) < 0 || int(board[y + 2, x - 1]) == 0)
							result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));

					if (piecePosition.X - 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 1 > -1)
						if (int(board[y - 2, x - 1]) < 0 || int(board[y - 2, x - 1]) == 0)
							result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (piecePosition.X + 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X + 2 > -1)
						if (int(board[y + 1, x + 2]) < 0 || int(board[y + 1, x + 2]) == 0)
							result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));

					if (piecePosition.X + 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X + 2 > -1)
						if (int(board[y - 1, x + 2]) < 0 || int(board[y - 1, x + 2]) == 0)
							result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));

					if (piecePosition.X - 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X - 2 > -1)
						if (int(board[y + 1, x - 2]) < 0 || int(board[y + 1, x - 2]) == 0)
							result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));

					if (piecePosition.X - 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X - 2 > -1)
						if (int(board[y - 1, x - 2]) < 0 || int(board[y - 1, x - 2]) == 0)
							result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));

				}
			}

			break;

			case BlackKnight:

			{
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;

				if (piecePosition.X + 2 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 2 > -1)
				{
					if (int(board[y + 2, x + 1]) > 0 || int(board[y + 2, x + 1]) == 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));

					if (int(board[y - 2, x + 1]) > 0 || int(board[y - 2, x + 1]) == 0)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));

					if (int(board[y + 2, x - 1]) > 0 || int(board[y + 2, x - 1]) == 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));

					if (int(board[y - 2, x - 1]) > 0 || int(board[y - 2, x - 1]) == 0)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (int(board[y + 1, x + 2]) > 0 || int(board[y + 1, x + 2]) == 0)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));

					if (int(board[y - 1, x + 2]) > 0 || int(board[y - 1, x + 2]) == 0)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));

					if (int(board[y + 1, x - 2]) > 0 || int(board[y + 1, x - 2]) == 0)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));

					if (int(board[y - 1, x - 2]) > 0 || int(board[y - 1, x - 2]) == 0)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));
				}
				else
				{
					if (piecePosition.X + 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X + 1 > -1)
						if (int(board[y + 2, x + 1]) > 0 || int(board[y + 2, x + 1]) == 0)
							result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));

					if (piecePosition.X + 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X + 1 > -1)
						if (int(board[y - 2, x + 1]) > 0 || int(board[y - 2, x + 1]) == 0)
							result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));

					if (piecePosition.X - 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X - 1 > -1)
						if (int(board[y + 2, x - 1]) > 0 || int(board[y + 2, x - 1]) == 0)
							result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));

					if (piecePosition.X - 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 1 > -1)
						if (int(board[y - 2, x - 1]) > 0 || int(board[y - 2, x - 1]) == 0)
							result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (piecePosition.X + 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X + 2 > -1)
						if (int(board[y + 1, x + 2]) > 0 || int(board[y + 1, x + 2]) == 0)
							result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));

					if (piecePosition.X + 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X + 2 > -1)
						if (int(board[y - 1, x + 2]) > 0 || int(board[y - 1, x + 2]) == 0)
							result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));

					if (piecePosition.X - 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X - 2 > -1)
						if (int(board[y + 1, x - 2]) > 0 || int(board[y + 1, x - 2]) == 0)
							result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));

					if (piecePosition.X - 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X - 2 > -1)
						if (int(board[y - 1, x - 2]) > 0 || int(board[y - 1, x - 2]) == 0)
							result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));
				}

			}

			break;

			case WhiteBishop:
			{
				bool Break = 0;
				for (int i = piecePosition.X + 1; i < 8; i++) // SE
				{
					for (int j = piecePosition.Y + 1 ; j < 8; j++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)                                           //////
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}

						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}
				Break = 0;

				for (int i = piecePosition.X - 1; i > -1; i--) //NW 
				{

					for (int j = piecePosition.Y - 1; j > -1; j--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y + 1; j < 8; j++) ///SW
				{

					for (int i = piecePosition.X - 1 ; i > -1; i--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)/////////
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y - 1; j > -1; j--) ///NE
				{

					for (int i = piecePosition.X + 1; i < 8; i++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}
				
				
				break;
			}
		
				
			case BlackBishop:
			{
				bool Break = 0;

				for (int i = piecePosition.X + 1; i < 8; i++) // SE
				{
					for (int j = piecePosition.Y + 1; j < 8; j++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)                                           //////
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}

						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}
				Break = 0;

				for (int i = piecePosition.X - 1; i > -1; i--) //NW 
				{

					for (int j = piecePosition.Y - 1; j > -1; j--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y + 1; j < 8; j++) ///SW
				{

					for (int i = piecePosition.X - 1; i > -1; i--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)/////////
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y - 1; j > -1; j--) ///NE
				{

					for (int i = piecePosition.X + 1; i < 8; i++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}


				break;
			}
			
			case WhiteQueen:
			{

				bool Break = 0;
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;
				for (int i = piecePosition.Y + 1; i < 8; i++)
				{
					if (int(board[i, piecePosition.X]) > 0)
						break;
					if (int(board[i, piecePosition.X]) < 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}
					result->Add(Point(piecePosition.X, i));
				}

				for (int i = piecePosition.Y - 1; i > -1; i--)
				{
					if (int(board[i, piecePosition.X]) > 0)
						break;
					if (int(board[i, piecePosition.X]) < 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}

					result->Add(Point(piecePosition.X, i));
				}
				/// ////
				for (int i = piecePosition.X + 1; i < 8; i++)
				{
					if (int(board[piecePosition.Y, i]) > 0)
						break;
					if (int(board[piecePosition.Y, i]) < 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X - 1; i > -1; i--)
				{
					if (int(board[piecePosition.Y, i]) > 0)
						break;
					if (int(board[piecePosition.Y, i]) < 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X + 1; i < 8; i++) // SE
				{
					for (int j = piecePosition.Y + 1; j < 8; j++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)                                           //////
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}

						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}
				Break = 0;

				for (int i = piecePosition.X - 1; i > -1; i--) //NW 
				{

					for (int j = piecePosition.Y - 1; j > -1; j--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y + 1; j < 8; j++) ///SW
				{

					for (int i = piecePosition.X - 1; i > -1; i--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)/////////
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y - 1; j > -1; j--) ///NE
				{

					for (int i = piecePosition.X + 1; i < 8; i++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) > 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) < 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}


				break;
			}

			/*
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (i - piecePosition.X == j - piecePosition.Y)
							result->Add(Point(i, j));
						else if (i - piecePosition.X == piecePosition.Y - j)
							result->Add(Point(i, j));
					}
					result->Add(Point(piecePosition.X, i));
					result->Add(Point(i, piecePosition.Y));
				}
				break;
					 */
			case BlackQueen:
			{
				bool Break = 0;
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;

				for (int i = piecePosition.Y + 1; i < 8; i++)
				{
					if (int(board[i, piecePosition.X]) < 0)
						break;
					if (int(board[i, piecePosition.X]) > 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}
					result->Add(Point(piecePosition.X, i));
				}

				for (int i = piecePosition.Y - 1; i > -1; i--)
				{
					if (int(board[i, piecePosition.X]) < 0)
						break;
					if (int(board[i, piecePosition.X]) > 0)
					{
						result->Add(Point(piecePosition.X, i));
						break;
					}

					result->Add(Point(piecePosition.X, i));
				}
				/// ////
				for (int i = piecePosition.X + 1; i < 8; i++)
				{
					if (int(board[piecePosition.Y, i]) < 0)
						break;
					if (int(board[piecePosition.Y, i]) > 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X - 1; i > -1; i--)
				{
					if (int(board[piecePosition.Y, i]) < 0)
						break;
					if (int(board[piecePosition.Y, i]) > 0)
					{
						result->Add(Point(i, piecePosition.Y));
						break;
					}
					result->Add(Point(i, piecePosition.Y));

				}
				for (int i = piecePosition.X + 1; i < 8; i++) // SE
				{
					for (int j = piecePosition.Y + 1; j < 8; j++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)                                           //////
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}

						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}
				Break = 0;

				for (int i = piecePosition.X - 1; i > -1; i--) //NW 
				{

					for (int j = piecePosition.Y - 1; j > -1; j--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y + 1; j < 8; j++) ///SW
				{

					for (int i = piecePosition.X - 1; i > -1; i--)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
						else if (i - piecePosition.X == piecePosition.Y - j)/////////
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}

						}
					}

					if (Break)
						break;
				}

				Break = 0;

				for (int j = piecePosition.Y - 1; j > -1; j--) ///NE
				{

					for (int i = piecePosition.X + 1; i < 8; i++)
					{

						if (i - piecePosition.X == j - piecePosition.Y)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
						else if (i - piecePosition.X == piecePosition.Y - j)
						{
							if (int(board[j, i]) < 0)
							{
								if (i == piecePosition.X && j == piecePosition.Y)
									continue;
								Break = 1;
								break;
							}

							if (int(board[j, i]) > 0)
							{
								result->Add(Point(i, j));
								Break = 1;
								break;
							}
							else
							{
								result->Add(Point(i, j));
								break;
							}
						}
					}

					if (Break)
						break;
				}


				break;
			}
           
				////////////////////////////KING
			case WhiteKing:
			{
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;

				// y + 1 < 8
				// x + 1 < 8
				// y - 1 > -1
				// x - 1 > -1

				if (y + 1 < 8 && (int(board[y + 1, x]) < 0 || int(board[y + 1, x]) == 0))
				result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				if (y - 1 > -1 && ( int(board[y - 1, x]) < 0 || int(board[y - 1, x]) == 0))
				result->Add(Point(piecePosition.X, piecePosition.Y - 1));
				if (x + 1 < 8 && (int(board[y , x + 1]) < 0 || int(board[y , x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y));
				if (x - 1 > -1 && ( int(board[y , x - 1]) < 0 || int(board[y, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y));

				if (y + 1 < 8 && y + 1 < 8 && (int(board[y + 1, x + 1]) < 0 || int(board[y + 1, x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
				if (x + 1 < 8 && y - 1 > -1 && (int(board[y - 1, x + 1]) < 0 || int(board[y - 1, x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
				if (x - 1 > -1 && y - 1 > -1 && (int(board[y - 1, x - 1]) < 0 || int(board[y - 1, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
				if (y + 1 < 8 && x - 1 > -1 && (int(board[y + 1, x - 1]) < 0 || int(board[y + 1, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
				break;
			}
				
			case BlackKing:
			{
			// y + 1 < 8
			// x + 1 < 8
			// y - 1 > -1
			// x - 1 > -1
				int x = 0, y = 0;
				x = piecePosition.X;
				y = piecePosition.Y;
				if (y + 1 < 8 && (int(board[y + 1, x] ) > 0 || int(board[y + 1, x ]) == 0))
				result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				if (y - 1 > -1 && (int(board[y - 1, x ]) > 0 || int(board[y - 1, x ]) == 0))
				result->Add(Point(piecePosition.X, piecePosition.Y - 1));
				if (x + 1 < 8 && (int(board[y , x + 1]) > 0 || int(board[y , x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y));
				if (x - 1 > -1 && (int(board[y, x - 1]) > 0 || int(board[y, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y));

				if (x + 1 < 8 && y + 1 < 8 &&( int(board[y + 1, x + 1]) > 0 || int(board[y + 1, x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
				if (x + 1 < 8 && y - 1 > -1 && (int(board[y - 1, x + 1]) > 0 || int(board[y - 1, x + 1]) == 0))
				result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
				if (y - 1 > -1 && x-1>-1 &&(int(board[y - 1, x - 1]) > 0 || int(board[y - 1, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
				if (y+1<8 && x-1 > -1 && (int(board[y + 1, x - 1]) > 0 || int(board[y + 1, x - 1]) == 0))
				result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
				break;
			
			}
				
			}

			return result;
		}

		bool EndTheGame(Point piecePosition) // 1 = White is winner , 0 = Black is winner
		{
			bool ExistWhiteKing = 0;
			bool ExistBlackKing = 0;
			auto result = gcnew List<Point>();
			auto piece = board[piecePosition.Y, piecePosition.X];
			bool isWhite = int(piece) > 0;
			for (int i = 0; i < 8; i++)
			{
				for (int j; j < 8; j++)
				{
					if (int(board[j, i]) == WhiteKing)
						ExistWhiteKing = 1;
					if (int(board[j, i]) == BlackKing)
						ExistWhiteKing = 1;
				}
			}
			if (!ExistWhiteKing)
				return 0;
			if (!ExistBlackKing)
				return 1;
			
		
		}
		ChessPieces move(Point lastPiecePosition, Point newPiecePosition) {
			auto
				peice = board[lastPiecePosition.Y, lastPiecePosition.X],
				LastPiece = board[newPiecePosition.Y, newPiecePosition.X];

			board[lastPiecePosition.Y, lastPiecePosition.X] = Empty;
			board[newPiecePosition.Y, newPiecePosition.X] = peice;

			return LastPiece;
		}
	};

	public ref class ChessBoard
	{
	private:
		Form^ mainForm;
		cli::array<Button^>^ btns = gcnew cli::array<Button^>(64);

		int offsetX, offsetY, cellSize;
		ThemeOptions^ theme;
		BoardClass^ boardclass;
		Action<Point>^ whenClicked;
	public:

		ChessBoard(
			Form^ mf,
			int offx, int offy,
			int _cellSize,
			ThemeOptions^ to,
			BoardClass^ bc,
			Action<Point>^ _whenClicked
		) : mainForm(mf),
			offsetX(offx), offsetY(offy), cellSize(_cellSize),
			theme(to),
			boardclass(bc),
			whenClicked(_whenClicked)
		{}

		void firstDraw() {
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					auto btn = btns[y * 8 + x] = gcnew Button();

					// add style to button
					btn->Location = Point(offsetX + cellSize * x, offsetY + cellSize * y);
					btn->Size = DSize(cellSize, cellSize);
					btn->FlatAppearance->BorderSize = 0;
					btn->FlatStyle = FlatStyle::Flat;

					// add click event
					auto lw = gcnew UiEventLambdaWrapper<Point>();
					lw->valToPass = Point(x, y);
					lw->nextFunc = whenClicked;
					btn->Click += gcnew EventHandler(lw, &UiEventLambdaWrapper<Point>::func);

					// add button to window
					mainForm->Controls->Add(btn);
				}
			}

			render();
		}
		void render() {
			mainForm->SuspendLayout();

			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					auto btn = btns[y * 8 + x];
					auto piece = boardclass->board[y, x];

					// set cell piece image
					if (piece != Empty) {
						auto themeStyle = theme->pieciesThemeStyle;
						auto pieceColor = theme->pieciesThemeColor;

						string imagePath = "themes\\" +
							PieciesThemeStyleString[themeStyle] + "\\" +
							PieciesThemeColorString[pieceColor] + "\\" +
							peiceFileName[piece];

						btn->Image = safe_cast<Image^>(
							gcnew Bitmap(
								Image::FromFile(currentDir() + gcnew String(imagePath.c_str())),
								DSize(cellSize * 0.8, cellSize)
							));

					}
					else {
						btn->Image = safe_cast<Image^>(gcnew Bitmap(1, 1)); // empty image
					}

					// set cell color
					auto selectedBackTheme = theme->boardBackTheme;
					auto backtheme = BackThemes[selectedBackTheme];
					MyColor c;
					if ((x + y) % 2 == 0) c = backtheme[0];
					else c = backtheme[1];

					btn->BackColor = Color::FromArgb(c.r, c.g, c.b);
				}
			}

			/// move points
			for (int i = 0; i < boardclass->movePoints->Count; i++) {
				auto p = boardclass->movePoints[i];
				if (0 <= p.Y * 8 + p.X && p.Y * 8 + p.X < 64)
				{
					auto btn = btns[p.Y * 8 + p.X];
					btn->BackColor = Color::SkyBlue;
				}

			}
			/// danger points
			for (int i = 0; i < boardclass->dangerPoints->Count; i++) {
				auto p = boardclass->dangerPoints[i];
				auto btn = btns[p.Y * 8 + p.X];

				btn->BackColor = Color::Red;
			}

			mainForm->ResumeLayout(false);
		};
	};
}