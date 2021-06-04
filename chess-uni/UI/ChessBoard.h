#pragma once
#include "../utils/lambda.h"

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	public ref class ChessBoard
	{
	private:
		Form^ mainForm;
		int size = 50;
		array<Button^>^ btns = gcnew array<Button^>(64);

	public:
		ChessBoard(Form^ mf, int offsetX, int offsetY, Action<Point>^ whenClicked)
		{
			this->mainForm = mf;

			for (int y = 0; y < 8; y++)
				for (int x = 0; x < 8; x++) {
					auto btn = btns[y * 8 + x] = gcnew Button();

					// add style to button
					btn->Location = Point(offsetX + size * x, offsetY + size * y);
					btn->Size = DSize(size, size);
					btn->Text = L"X";
					btn->UseVisualStyleBackColor = true;

					// add click event
					auto lw = gcnew UiEventLambdaWrapper<Point>();
					lw->valToPass = Point(x, y);
					lw->nextFunc = whenClicked;
					btn->Click += gcnew EventHandler(lw, &UiEventLambdaWrapper<Point>::func);
					
					// add button to window
					mf->Controls->Add(btn);

					// dsadk  sdsd 
					int a = 3;

				}
		}
		~ChessBoard() {	}
	};
};