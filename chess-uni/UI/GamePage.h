#pragma once

#include "../include/json.hpp"

#include "Timer.h"
#include "ChessBoard.h"
#include "../modules/soc.hpp"

extern SocketAbs *appSocket;

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	int
		windowWidth = 1000, windowHeight = 800,
		offsetX = 50, offsetY = 100;

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
		ThemeOptions^ theme = gcnew ThemeOptions();
		ChessBoard^ boardComponent;
		BoardClass^ boardclass = gcnew BoardClass();
		Timerrr^ timer;

		void InitializeComponent(void)
		{
			// create window
			this->Text = L"chess";
			this->Size = DSize(windowWidth, windowHeight);
			this->BackColor = Color::White;

			// init chess board
			boardComponent = gcnew ChessBoard(this,
				offsetX, offsetY, 80,
				theme,
				boardclass,
				gcnew Action<Point>(this, &GamePage::whenClickedOnCell)
			);

			// init timer
			timer = gcnew Timerrr(this, offsetX / 2, offsetY / 2);

			// init music player
			//auto mp = gcnew UI::MusicPlayer(this, 300, 50);

			// set form events
			this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
		}

		void whenClickedOnCell(Point p) {
			boardclass->movePoints = boardclass->possibleMoves(p);
			boardComponent->render();
		}

		void onHey(json js) {
			Console::WriteLine(js.dump().c_str());
		}
		void OnLoad(Object^ sender, EventArgs^ e) {
			// register socket events
			SocketInterop::on("salam", gcnew JsonReciever(this, &GamePage::onHey));
			SocketInterop::run();

			boardComponent->firstDraw();
			timer->setTime(5 * 60 * 60);
			timer->start();
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			timer->stop();

			// remove socket events
		}
	};
}