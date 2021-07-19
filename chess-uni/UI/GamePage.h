#pragma once
#include "../include/json.hpp"

#include "Timer.h"
#include "ChessBoard.h"
#include "MusicPlayer.h"
#include "../modules/socketio.hpp"
#include "../utils/gameLogic.h"

extern SocketAbs* appSocket;

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	int
		windowWidth = 1000, windowHeight = 840,
		offsetX = 50, offsetY = 140;

	bool isSelectingCell = false;
	Point lastSelectedCell;

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
		Timerr^ timer;

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
			timer = gcnew Timerr(this, offsetX / 2, offsetY / 2);

			//init music player
			auto mp = gcnew chessuni::musicPlayer(this->Controls);
			mp->setOffset(700, 40);

			// set form events
			this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
		}

		void whenClickedOnCell(Point p) {
			if (isSelectingCell) {
				if (contains(boardclass->movePoints, p)) {
					auto removedPiece = boardclass->move(lastSelectedCell, p);
				}

				boardclass->movePoints->Clear();
				isSelectingCell = false;
			}
			else {
				isSelectingCell = true;
				lastSelectedCell = p;
				boardclass->movePoints = boardclass->possibleMoves(p);
			}

			boardComponent->render();
		}
		void onMove(json data) {
			Console::WriteLine(data.dump().c_str());
		}
		void onGameBegin(json data) {
			timer->setTime(data["time"].get<int>());
			timer->start();
		}

		void OnLoad(Object^ sender, EventArgs^ e) {
			// register socket events
			SocketInterop::on("move", gcnew JsonReciever(this, &GamePage::onMove));
			SocketInterop::on("begin", gcnew JsonReciever(this, &GamePage::onGameBegin));

			boardComponent->firstDraw();
			timer->setTime(0);
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			SocketInterop::removeAll();
			timer->stop();
		}
	};
}