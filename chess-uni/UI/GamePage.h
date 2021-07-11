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

	int
		windowWidth = 1000, windowHeight = 800,
		offsetX = 50, offsetY = 100
		;

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
		ThemeOptions^ theme = gcnew ThemeOptions();
		ChessBoard^ board;
		Timerrr^ timer;

		void InitializeComponent(void)
		{
			// create window
			this->Text = L"chess game";
			this->Size = DSize(windowWidth, windowHeight);
			this->BackColor = Color::White;

			// init chess board
			board = gcnew ChessBoard(this,
				offsetX, offsetY, 80,
				theme,
				gcnew Action<Point>(this, &GamePage::whenClickedOnCell)
			);

			// init timer
			timer = gcnew Timerrr(this, offsetX / 2, offsetY / 2);

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

		void whenClickedOnCell(Point p) {
			// it shows the position like "(x, y)"
			lastAction->Text =
				L"(" + p.X.ToString() + ", " + p.Y.ToString() + L")";
		}

		void OnLoad(Object^ sender, EventArgs^ e) {
			board->firstDraw();
			timer->setTime(5 * 60 * 60);
			timer->start();
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			timer->stop();
		}
	};
}