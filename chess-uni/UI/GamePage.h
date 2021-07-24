#pragma once
#include "../include/json.hpp"

#include "Timer.h"
#include "ChessBoard.h"
#include "IntroPage.h"
#include "MusicPlayer.h"
#include "../modules/socketio.hpp"
#include "../modules/database.h"
#include "../utils/gameLogic.h"
#include "../utils/fileio.h"
#include "../utils/ui.h"
#include "./selectOption.h"


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
		// visual components
		IContainer^ components;
		ChessBoard^ boardComponent;
		Timerr^ timer;
		Label^ roleLabel;
		GroupBox^ settings;
		chessuni::musicPlayer^ mp;

		// state components
		AppStates^ as = gcnew AppStates();
		BoardClass^ boardclass = gcnew BoardClass();
		ThemeOptions^ theme = gcnew ThemeOptions();

		bool
			isSelectingCell = false,
			isMyTrun = false;

		Point lastSelectedCell;


		void InitializeComponent()
		{
			// create window -----------------------------------
			this->Text = L"chess";
			this->Size = DSize(windowWidth, windowHeight);
			this->BackColor = Color::White;

			roleLabel = gcnew Label();
			roleLabel->Text = gcnew String(
				*UI::userRole == ServerRole ? "server" : "client"
			);
			roleLabel->Location = Point(10, 20);
			roleLabel->AutoSize = true;
			roleLabel->Font = gcnew Drawing::Font(
				L"Guttman-CourMir", 20, FontStyle::Regular, GraphicsUnit::Point, 0);
			this->Controls->Add(roleLabel); // add label to window

			// settings -------------------------------------
			settings = gcnew GroupBox();
			settings->Width = 100;
			settings->AutoSize = true;
			settings->Location = Point(760, 280);

			auto so1 = gcnew SelectOption(
				settings->Controls,
				"board bg",
				gcnew System::Drawing::Font(L"Guttman-CourMir", 14, FontStyle::Regular, GraphicsUnit::Point, 0),
				140, 30,
				0, 0
			);

			for (map<BoardBackTheme, string>::iterator  it = BoardBackThemeString.begin(); it != BoardBackThemeString.end(); it++)
			{
				so1->addOption(
					it->second,
					int(it->first),
					gcnew Action<int>(this, &GamePage::onBoardThemeChange)
				);
			}

			auto so2 = gcnew SelectOption(
				settings->Controls,
				"piece color",
				gcnew System::Drawing::Font(L"Guttman-CourMir", 14, FontStyle::Regular, GraphicsUnit::Point, 0),
				140, 30,
				0, 140
			);

			for (map<PieciesThemeColor, string> ::iterator it = PieciesThemeColorString.begin(); it != PieciesThemeColorString.end(); it++)
			{
				so2->addOption(
					it->second,
					int(it->first),
					gcnew Action<int>(this, &GamePage::onPieceColorChange)
				);
			}

			auto so3 = gcnew SelectOption(
				settings->Controls,
				"piece style",
				gcnew System::Drawing::Font(L"Guttman-CourMir", 14, FontStyle::Regular, GraphicsUnit::Point, 0),
				140, 30,
				0, 280
			);

			for (map<PieciesThemeStyle, string>::iterator  it = PieciesThemeStyleString.begin(); it != PieciesThemeStyleString.end(); it++)
			{
				so3->addOption(
					it->second,
					int(it->first),
					gcnew Action<int>(this, &GamePage::onPieceStyleChange)
				);
			}

			this->Controls->Add(settings);
			// init chess board ---------------------------------
			boardComponent = gcnew ChessBoard(this,
				offsetX, offsetY, 80,
				theme,
				boardclass,
				gcnew Action<Point>(this, &GamePage::OnClickedOnCell)
			);

			// init timer
			timer = gcnew Timerr(this, offsetX / 2, offsetY / 2);

			//init music player
			mp = gcnew chessuni::musicPlayer(
				as,
				this->Controls,
				gcnew OnNewFileSelected(this, &GamePage::onNewMusicSelected)
			);
			mp->setOffset(700, 40);


			// set form events
			this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
		}

		/// form events ----------------------------------------------
		void OnLoad(Object^ sender, EventArgs^ e) {
			// register socket events
			SocketInterop::on("move", gcnew JsonReciever(this, &GamePage::onMove));
			SocketInterop::on("setting", gcnew JsonReciever(this, &GamePage::onSettingChange));

			// init enviroment
			as->board = boardclass->board;
			as->selectedTheme = theme;

			if (*UI::userRole == ServerRole)
				isMyTrun = true;

			// prepare UI
			boardComponent->firstDraw();

			timer->setTime(30 * 60);
			timer->start();

			mp->setUImode();
			if (*UI::userRole == ClientRole)
				mp->hide();
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			SocketInterop::removeAll();
			timer->stop();
		}
		void OnClickedOnCell(Point p) {
			if (!isMyTrun) return;

			if (isSelectingCell) {
				if (contains(boardclass->movePoints, p)) {

					SocketInterop::sendNtrigger("move", json{
						{"from", {lastSelectedCell.X, lastSelectedCell.Y}},
						{"to",   {p.X, p.Y}},
						});
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
		void onMusicSelected(string name) {

		}
		void onNewMusicSelected(string fpath, string fname)
		{
			// send the file
		}
		void onBoardThemeChange(int newColor) {
			theme->boardBackTheme = BoardBackTheme(newColor);
			SocketInterop::sendNtrigger("setting", as->serialize());
		}
		void onPieceStyleChange(int newColor) {
			theme->pieciesThemeStyle= PieciesThemeStyle(newColor);
			SocketInterop::sendNtrigger("setting", as->serialize());
		}
		void onPieceColorChange(int newColor) {
			theme->pieciesThemeColor= PieciesThemeColor(newColor);
			SocketInterop::sendNtrigger("setting", as->serialize());
		}

		/// socket events ----------------------------------------------
		void onMove(json data) {
			auto
				p1 = Point(data["from"][0].get<int>(), data["from"][1].get<int>()),
				p2 = Point(data["to"][0].get<int>(), data["to"][1].get<int>());

			boardclass->move(p1, p2);
			boardComponent->render();

			isMyTrun = !isMyTrun;
		}
		void onSettingChange(json data) {
			as->deserialize(data);

			if (as->IsMusicPlaying)
				mp->Play();
			else
				mp->Pause();

			this->boardclass->board = as->board;
			theme = as->selectedTheme;

			// move preview
			// selected music

			this->boardComponent->render();
		}
	};
}