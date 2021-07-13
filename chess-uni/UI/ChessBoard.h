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
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
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

			switch (piece)
			{
			case Empty:
				break;

			case WhitePawn:
			case BlackPawn:
				result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
				break;

			case WhiteRook:
			case BlackRook:
				break;

			case WhiteKnight:
			case BlackKnight:
				break;

			case WhiteBishop:
			case BlackBishop:
				break;

			case WhiteQueen:
			case BlackQueen:
				break;

			case WhiteKing:
			case BlackKing:
				break;
			}

			return result;
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
						string imagePath = "themes\\" +
							PieciesThemeStyleString[theme->pieciesThemeStyle] + "\\" +
							PieciesThemeColorString[theme->pieciesThemeColor] + "\\" +
							peiceFileName[piece];

						// scale image to fit into the cell
						btn->Image = safe_cast<Image^>(
							gcnew Bitmap(
								Image::FromFile(currentDir() + gcnew String(imagePath.c_str())),
								DSize(cellSize * 0.8, cellSize)
							));
					}
					else {
						delete btn->Image;
					}

					// set cell color
					auto backtheme = BackThemes[theme->boardBackTheme];
					MyColor c;
					if ((x + y) % 2 == 0) c = backtheme[0];
					else c = backtheme[1];

					btn->BackColor = Color::FromArgb(c.r, c.g, c.b);
				}
			}

			/// move points
			for (int i = 0; i < boardclass->movePoints->Count; i++) {
				auto p = boardclass->movePoints[i];
				auto btn = btns[p.Y * 8 + p.X];

				btn->BackColor = Color::SkyBlue;
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