#pragma once
#include "../include/json.hpp"

#include <base64.h>
#include <json.hpp>
#include "Timer.h"
#include "ChessBoard.h"
#include "IntroPage.h"
#include "MusicPlayer.h"
#include "../modules/socketio.hpp"
#include "../modules/database.h"
#include "../utils/gameLogic.h"
#include "../utils/fileio.h"
#include "../utils/ui.h"
#include "../utils/utils.h"
#include "./selectOption.h"

using json = nlohmann::json;
extern SocketAbs* appSocket;

namespace UI {
	using namespace System;
	using namespace System::Collections::Generic;
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
		Label^ roleLabel;
		Timerr^ timer;
		chessuni::musicPlayer^ mp;
		GroupBox^ settings;
		CheckBox^ showMovePreviewCheckBox;
		CheckBox^ showTimerCheckBox;

		// state components
		AppStates^ as = gcnew AppStates();
		BoardClass^ boardclass = gcnew BoardClass();
		ThemeOptions^ theme = gcnew ThemeOptions();

		bool
			isSelectingCell = false,
			isMyTrun = false;

		Point lastSelectedCell;

		Generic::Queue<MyFileInfo^>^ filesToSendQueue =
			gcnew Generic::Queue<MyFileInfo^>();


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
			auto settings_font = gcnew System::Drawing::Font(L"Guttman-CourMir", 10, FontStyle::Regular, GraphicsUnit::Point, 0);

			settings = gcnew GroupBox();
			settings->Width = 100;
			settings->AutoSize = true;
			settings->Location = Point(760, 280);

			auto so1 = gcnew SelectOption(
				settings->Controls,
				"board bg",
				settings_font,
				140, 30,
				0, 0
			);

			for (map<BoardBackTheme, string>::iterator it = BoardBackThemeString.begin(); it != BoardBackThemeString.end(); it++)
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
				settings_font,
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
				settings_font,
				140, 30,
				0, 280
			);

			for (map<PieciesThemeStyle, string>::iterator it = PieciesThemeStyleString.begin(); it != PieciesThemeStyleString.end(); it++)
			{
				so3->addOption(
					it->second,
					int(it->first),
					gcnew Action<int>(this, &GamePage::onPieceStyleChange)
				);
			}

			showMovePreviewCheckBox = gcnew CheckBox();
			showMovePreviewCheckBox->AutoSize = true;
			showMovePreviewCheckBox->Location = System::Drawing::Point(0, 400);
			showMovePreviewCheckBox->Text = L"show move preview";
			showMovePreviewCheckBox->Font = settings_font;
			showMovePreviewCheckBox->Click += gcnew EventHandler(this, &GamePage::checkBox1_Click);

			showTimerCheckBox = gcnew CheckBox();
			showTimerCheckBox->AutoSize = true;
			showTimerCheckBox->Location = System::Drawing::Point(0, 430);
			showTimerCheckBox->Text = L"show timer";
			showTimerCheckBox->Font = settings_font;
			showTimerCheckBox->Click += gcnew EventHandler(this, &GamePage::checkBox2_Click);


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
				gcnew OnNewFileSelectedEvent(this, &GamePage::onNewMusicSelected),
				gcnew OnMusicChangedEvent(this, &GamePage::onMusicChanged),
				gcnew OnPlayStateChangeEvent(this, &GamePage::onPlayStateChanged)
			);
			mp->setOffset(700, 40);


			settings->Controls->Add(showMovePreviewCheckBox);
			settings->Controls->Add(showTimerCheckBox);
			this->Controls->Add(settings);

			// set form events
			this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
		}

		/// form events ----------------------------------------------
		void OnLoad(Object^ sender, EventArgs^ e) {
			// register socket events
			SocketInterop::on("move", gcnew JsonReciever(this, &GamePage::onMove));
			SocketInterop::on("setting", gcnew JsonReciever(this, &GamePage::onSettingChange));
			SocketInterop::on("file", gcnew JsonReciever(this, &GamePage::onFileRecv));

			// init enviroment
			as->board = boardclass->board;
			as->selectedTheme = theme;

			if (*UI::userRole == ServerRole)
				isMyTrun = true;
			else
				settings->Visible = false;

			// prepare UI
			boardComponent->firstDraw();
			showMovePreviewCheckBox->Checked = as->selectedTheme->showMovePreview;
			showTimerCheckBox->Checked = as->showTimer;
			timer->setVisibility(as->showTimer);
			timer->setTime(30 * 60);
			timer->start();

			mp->initUI();
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
		void checkBox1_Click(Object^ sender, EventArgs^ e) {
			theme->showMovePreview = showMovePreviewCheckBox->Checked;
			SocketInterop::sendNtrigger("setting", as->serialize());
		}
		void checkBox2_Click(Object^ sender, EventArgs^ e) {
			as->showTimer = showTimerCheckBox->Checked;
			SocketInterop::sendNtrigger("setting", as->serialize());
		}

		void onMusicChanged(string fname) {
			as->selectedMusic = gcnew String(fname.c_str());
		}
		void onPlayStateChanged(int stateCode) {
			as->IsMusicPlaying = (stateCode == PLAYING);

			if (*UI::userRole == ServerRole)
				SocketInterop::send("setting", as->serialize());
		}
		void onNewMusicSelected(string fpath, string fname)
		{
			auto fi = gcnew MyFileInfo();
			fi->name = gcnew String(fname.c_str());;
			fi->path = gcnew String(fpath.c_str());;
			filesToSendQueue->Enqueue(fi);

			auto t = gcnew Thread(gcnew ThreadStart(this, &GamePage::sendMusicBackground));
			t->Start();
		}
		void sendMusicBackground() {
			auto fi = filesToSendQueue->Dequeue();
			auto content = base64_encode(readFile(toStdString(fi->path)));
			SocketInterop::send("file", json{
				{"type", "music"},
				{"name", toStdString(fi->name)},
				{"content", content},
				});
		}

		void onBoardThemeChange(int newColor) {
			theme->boardBackTheme = BoardBackTheme(newColor);
			SocketInterop::sendNtrigger("setting", as->serialize());
		}
		void onPieceStyleChange(int newColor) {
			theme->pieciesThemeStyle = PieciesThemeStyle(newColor);
			SocketInterop::sendNtrigger("setting", as->serialize());
		}
		void onPieceColorChange(int newColor) {
			theme->pieciesThemeColor = PieciesThemeColor(newColor);
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
			auto lastMusicName = as->selectedMusic;
			Console::WriteLine(gcnew String(
				data.dump().c_str()));

			as->deserialize(data);

			if (as->selectedMusic != lastMusicName)
				mp->selectMusicByName(as->selectedMusic);

			if (as->IsMusicPlaying)
				mp->Play();
			else
				mp->Pause();


			this->boardclass->board = as->board;
			theme = as->selectedTheme;

			showMovePreviewCheckBox->Checked = theme->showMovePreview;
			timer->setVisibility(as->showTimer);

			this->boardComponent->render();
		}
		void onFileRecv(json data) {
			auto
				content = base64_decode(data["content"].get<string>()),
				fname = data["name"].get<string>(),
				fpath = "musics/" + fname;
				
			writeFile(fpath, content);
			mp->addMusic(fname, fpath);
		}
	};
}