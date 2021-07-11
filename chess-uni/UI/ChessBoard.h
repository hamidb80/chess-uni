#pragma once
#include <string>
#include <map>
#include <vector>

#include "../utils/lambda.h"
#include "../utils/gameLogic.h"
#include "../utils/ui.h"
using namespace std;

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
	using DSize = System::Drawing::Size;

	public ref struct ThemeOptions {
		PieciesThemeColor pieciesThemeColor = Pink;
		BoardBackTheme boardBackTheme = MagicalMysteryRide;
		PieciesThemeStyle pieciesThemeStyle = Solid;
	};

	public ref class ChessBoard
	{
	private:
		Form^ mainForm;
		cli::array<Button^>^ btns = gcnew cli::array<Button^>(64);

		int offsetX, offsetY, cellSize;
		ThemeOptions^ theme;
		Action<Point>^ whenClicked;

	public:
		ChessBoard(
			Form^ mf,
			int offx, int offy,
			int _cellSize,
			ThemeOptions^ to,
			Action<Point>^ _whenClicked
		) : mainForm(mf),
			offsetX(offx), offsetY(offy), cellSize(_cellSize),
			theme(to),
			whenClicked(_whenClicked)
		{
			firstDraw();
		}

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

			render(startingPeiceOrder);
		}
		void render(ChessPieces boardmap[8][8]) {
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					auto btn = btns[y * 8 + x];
					auto piece = boardmap[y][x];

					// set cell piece image
					if (piece != Empty) {
						string imagePath = "themes\\" +
							PieciesThemeStyleString[theme->pieciesThemeStyle] + "\\" +
							PieciesThemeColorString[theme->pieciesThemeColor] + "\\" +
							peiceFileName[boardmap[y][x]];

						// scale image to fit into the cell
						btn->Image = safe_cast<Image^>(
							gcnew Bitmap(
								Image::FromFile(currentDir() + gcnew String(imagePath.c_str())),
								DSize(cellSize * 0.8, cellSize)
							));
					}


					// set cell color
					auto backtheme = BackThemes[theme->boardBackTheme];
					MyColor c;
					if ((x + y) % 2 == 0) c = backtheme[0];
					else c = backtheme[1];

					btn->BackColor = Color::FromArgb(c.r, c.g, c.b);
				}
			}
		};
	};
}