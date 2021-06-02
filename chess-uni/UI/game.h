#pragma once
#include "timer.h"

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	generic<class Type>
		ref class lambdaWrapper {
		public:
			Type valToPass;
			Action<Type>^ nextFunc;
			void func(Object^ sender, EventArgs^ e) {
				nextFunc(valToPass);
			}
		};

		public ref class GamePage : public Form
		{
		public:
			GamePage(void)
			{
				InitializeComponent();
			}
			~GamePage()
			{
				if (components)
					delete components;
			}

		private:
			IContainer^ components;

			Label^ lastAction;
			array<Button^>^ boardBtns = gcnew array<Button^>(64);
			Timer^ timer;

			void whenClicked(Point p) {
				// it shows the position like "(x, y)"
				lastAction->Text =
					L"(" + p.X.ToString() + ", " + p.Y.ToString() + L")";
			}
			void InitializeComponent(void)
			{
				// create window
				this->AutoScaleDimensions = SizeF(14, 29);
				this->ClientSize = DSize(800, 600);
				this->Text = L"main window";

				// create chess board
				int
					size = 50,
					offsetY = 100,
					offsetX = 50;
				
				for (int y = 0; y < 8; y++)
					for (int x = 0; x < 8; x++) {
						auto btn = boardBtns[y * 8 + x] = gcnew Button();
							
						btn->Location = Point(offsetX + size * x, offsetY + size * y);
						btn->Size = DSize(size, size);
						btn->Text = L"X";
						btn->UseVisualStyleBackColor = true;

						auto lw = gcnew lambdaWrapper<Point>();
						lw->valToPass = Point(x, y);
						lw->nextFunc = gcnew Action<Point>(this, &GamePage::whenClicked);
						btn->Click += gcnew EventHandler(lw, &lambdaWrapper<Point>::func);
						
						this->Controls->Add(btn);
					}

				// timer
				timer = gcnew UI::Timer(this, offsetX / 2, offsetY / 2);
				timer->setTime(5 * 60 * 60);

				// label
				lastAction = gcnew Label();
				lastAction->Location = Point(20, 10);
				lastAction->AutoSize = true;
				lastAction->Text = L"None";

				this->Controls->Add(lastAction);

				// set form events
				this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
				this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
			}

			void OnLoad(Object^ sender, EventArgs^ e) {
				timer->start();
			}
			void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
				timer->stop();
			}
		};
}
