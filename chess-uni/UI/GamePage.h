#pragma once
#include "../include/json.hpp"

#include "Timer.h"
#include "ChessBoard.h"
#include "IntroPage.h"
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

	public ref class GamePage : public Form
	{
	public:
		bool
			isSelectingCell = false,
			isMyTrun = false;
		
		Point lastSelectedCell;


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
		Label^ roleLabel = gcnew Label();

		void InitializeComponent(void)
		{
			// create window
			this->Text = L"chess";
			this->Size = DSize(windowWidth, windowHeight);
			this->BackColor = Color::White;

			roleLabel->Text = gcnew String(
				*UI::userRole == ServerRole ? "server" : "client"
			);
			roleLabel->Location = Point(10, 20);
			roleLabel->AutoSize = true;
			roleLabel->Font = gcnew Drawing::Font(
				L"Guttman-CourMir", 20, FontStyle::Regular, GraphicsUnit::Point, 0);


			this->Controls->Add(roleLabel); // add label to window

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

		/// form events ----------------------------------------------
		void OnLoad(Object^ sender, EventArgs^ e) {
			// register socket events
			SocketInterop::on("move", gcnew JsonReciever(this, &GamePage::onMove));
			SocketInterop::on("setting-change", gcnew JsonReciever(this, &GamePage::onSettingChange));

			// init enviroment
			if (*UI::userRole == ServerRole)
				isMyTrun = true;

			// prepare UI
			boardComponent->firstDraw();
			timer->setTime(30 * 60);
			timer->start();
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			SocketInterop::removeAll();
			timer->stop();
		}
		void whenClickedOnCell(Point p) {
			if (!isMyTrun) return;

			if (isSelectingCell) {
				if (contains(boardclass->movePoints, p)) {
					auto removedPiece = boardclass->move(lastSelectedCell, p);

					SocketInterop::send("move", json{
						{"from", {lastSelectedCell.X, lastSelectedCell.Y}},
						{"to",   {p.X, p.Y}},
						});

					isMyTrun = false;
				}

				boardclass->movePoints->Clear();
				isSelectingCell = false;
			}
			else {
				// check user clicked on a valid cell or not
				if (!(
					(*UI::userRole == ServerRole && isWhite(boardclass->board[p.Y, p.X])) ||
					(*UI::userRole == ClientRole && isBlack(boardclass->board[p.Y, p.X]))
					)) return;

				isSelectingCell = true;
				lastSelectedCell = p;
				boardclass->movePoints = boardclass->possibleMoves(p);
			}

			boardComponent->render();
		}

		/// socket events ----------------------------------------------
		void onMove(json data) {
			auto
				p1 = Point(data["from"][0].get<int>(), data["from"][1].get<int>()),
				p2 = Point(data["to"][0].get<int>(), data["to"][1].get<int>());

			boardclass->move(p1, p2);
			boardComponent->render();

			isMyTrun = true;
		}
		void onSettingChange(json data) {

		}
	};
}