#pragma once
#include <string>

#include "../utils/lambda.h"
#include "../utils/gameLogic.h"
#include "../utils/ui.h"
using namespace std;

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	public struct themeOptions {
		PieciesThemeColor pieciesThemeColor = Pink;
		BoardBackTheme boardBackTheme = Wood;
		PieciesThemeStyle pieciesThemeStyle = Solid;
	};

	public ref class ChessBoard
	{
	private:
		Form^ mainForm;
		cli::array<Button^>^ btns = gcnew cli::array<Button^>(64);

		int offsetX, offsetY, cellSize;
		BoardBackTheme currentBackTheme = Wood;
		Action<Point>^ whenClicked;

	public:
		ChessBoard(
			Form^ mf,
			int offx, int offy,
			int _cellSize,
			Action<Point>^ _whenClicked
		) : mainForm(mf),
			offsetX(offx), offsetY(offy),
			cellSize(_cellSize), whenClicked(_whenClicked)
		{
			firstDraw();
		}
		//~ChessBoard() {}

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

		void render(ChessPieces boardmap[8][8]) {
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					auto btn = btns[y * 8 + x];
					auto backtheme = BackThemes[currentBackTheme];
					string imagePath = "" + peiceFileName[boardmap[y][x]];

					MyColor c;
					if ((x + y) % 2 == 0) c = backtheme[0];
					else c = backtheme[1];

					btn->BackColor = Color::FromArgb(c.r, c.g, c.b);
				}
			}
		};
	};
}