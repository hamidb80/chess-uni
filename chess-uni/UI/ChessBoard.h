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
		BoardBackTheme boardBackTheme = BlackWhite;
		PieciesThemeStyle pieciesThemeStyle = Solid;
		bool showMovePreview = true;
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
				///////////////////////////PAWN
			case WhitePawn:
				result->Add(Point(piecePosition.X, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X, piecePosition.Y - 2));
				break;
			case BlackPawn:
				result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				result->Add(Point(piecePosition.X, piecePosition.Y + 2));
				break;
				////////////////////////////ROOK
			case WhiteRook:
				int d[8];
				for (int i = 0; i < 8; i++)
				{
					result->Add(Point(piecePosition.X, i));
					result->Add(Point(i, piecePosition.Y));
				}
				break;
			case BlackRook:
				for (int i = 0; i < 8; i++)
				{
					result->Add(Point(piecePosition.X, i));
					result->Add(Point(i, piecePosition.Y));
				}
				break;
				////////////////////////////KNIGHT

			case WhiteKnight:
				if (piecePosition.X + 2 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 2 > -1)
				{
					result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));
					result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));
					result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));
					result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));
					result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));
					result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));
					result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));
				}
				else
				{
					if (piecePosition.X + 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X + 1 > -1)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));
					if (piecePosition.X + 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X + 1 > -1)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));
					if (piecePosition.X - 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X - 1 > -1)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));
					if (piecePosition.X - 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 1 > -1)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (piecePosition.X + 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X + 2 > -1)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));
					if (piecePosition.X + 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X + 2 > -1)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));
					if (piecePosition.X - 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X - 2 > -1)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));
					if (piecePosition.X - 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X - 2 > -1)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));

				}

				break;
			case BlackKnight:
				if (piecePosition.X + 2 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 2 > -1)
				{
					result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));
					result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));
					result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));
					result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));
					result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));
					result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));
					result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));
				}
				else
				{
					if (piecePosition.X + 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X + 1 > -1)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y + 2));
					if (piecePosition.X + 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X + 1 > -1)
						result->Add(Point(piecePosition.X + 1, piecePosition.Y - 2));
					if (piecePosition.X - 1 < 8 && piecePosition.Y + 2 < 8 && piecePosition.Y + 2 > -1 && piecePosition.X - 1 > -1)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y + 2));
					if (piecePosition.X - 1 < 8 && piecePosition.Y - 2 < 8 && piecePosition.Y - 2 > -1 && piecePosition.X - 1 > -1)
						result->Add(Point(piecePosition.X - 1, piecePosition.Y - 2));

					if (piecePosition.X + 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X + 2 > -1)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y + 1));
					if (piecePosition.X + 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X + 2 > -1)
						result->Add(Point(piecePosition.X + 2, piecePosition.Y - 1));
					if (piecePosition.X - 2 < 8 && piecePosition.Y + 1 < 8 && piecePosition.Y + 1 > -1 && piecePosition.X - 2 > -1)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y + 1));
					if (piecePosition.X - 2 < 8 && piecePosition.Y - 1 < 8 && piecePosition.Y - 1 > -1 && piecePosition.X - 2 > -1)
						result->Add(Point(piecePosition.X - 2, piecePosition.Y - 1));

				}


				break;

			case WhiteBishop:
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (i - piecePosition.X == j - piecePosition.Y)
							result->Add(Point(i, j));
						else if (i - piecePosition.X == piecePosition.Y - j)
							result->Add(Point(i, j));
					}
				}
				break;
			case BlackBishop:
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (i - piecePosition.X == j - piecePosition.Y)
							result->Add(Point(i, j));
						else if (i - piecePosition.X == piecePosition.Y - j)
							result->Add(Point(i, j));
					}
				}
				break;

			case WhiteQueen:
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

			case BlackQueen:
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

				////////////////////////////KING
			case WhiteKing:
				result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				result->Add(Point(piecePosition.X, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
				break;
			case BlackKing:
				result->Add(Point(piecePosition.X, piecePosition.Y + 1));
				result->Add(Point(piecePosition.X, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y + 1));
				result->Add(Point(piecePosition.X + 1, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y - 1));
				result->Add(Point(piecePosition.X - 1, piecePosition.Y + 1));
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

		void initUI() {
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
			if (theme->showMovePreview)
				for (int i = 0; i < boardclass->movePoints->Count; i++) {
					auto p = boardclass->movePoints[i];
					if (0 <= p.Y * 8 + p.X && p.Y * 8 + p.X < 64)
					{
						auto btn = btns[p.Y * 8 + p.X];

						btn->BackColor = boardclass->board[p.Y, p.X] != Empty ? 
							Color::PaleVioletRed : Color::SkyBlue;
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