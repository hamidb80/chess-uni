#pragma once

#include "Timer.h"
#include "ChessBoard.h"

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	public ref class GamePage : public Form
	{
	public:
		GamePage()
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
		ChessBoard^ board;
		Timer^ timer;

		void whenClickedOnCell(Point p) {
			// it shows the position like "(x, y)"
			lastAction->Text =
				L"(" + p.X.ToString() + ", " + p.Y.ToString() + L")";
		}
		void InitializeComponent(void)
		{
			// create window
			this->AutoScaleDimensions = SizeF(14, 29);
			this->ClientSize = DSize(800, 600);
			this->Text = L"chess game";

			int
				offsetY = 100,
				offsetX = 50;

			// init chess board
			board = gcnew ChessBoard(
				this, offsetX, offsetY,
				gcnew Action<Point>(this, &GamePage::whenClickedOnCell));

			// init timer
			timer = gcnew UI::Timer(this, offsetX / 2, offsetY / 2);
			timer->setTime(5 * 60 * 60);

			// init lastAction label
			lastAction = gcnew Label();
			lastAction->Location = Point(20, 10);
			lastAction->AutoSize = true;
			lastAction->Text = L"None";
			this->Controls->Add(lastAction);

			// init music player
			//auto mp = gcnew UI::MusicPlayer(this, 300, 50);

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