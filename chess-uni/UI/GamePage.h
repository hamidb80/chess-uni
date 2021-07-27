#pragma once
#include "../include/json.hpp"

#include <base64.h>
#include <json.hpp>
#include "Timer.h"
#include "ChessBoard.h"
#include "./WinDialog.h"
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
	using namespace System::Collections::Generic;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	int windowWidth = 940, windowHeight = 840,
		offsetX = 20, offsetY = 140;

	public ref class GamePage : public Form
	{
		String^ DBpath;
		int sessionId;

	public:
		GamePage()
		{
			sessionId = freakin_random_number();
			DBpath = gcnew String((toStdString(currentDir()) + "databases/" + to_string(sessionId) + ".json").c_str());
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
		Label^ sessionIdLabel;
		Timerr^ timer;
		chessuni::musicPlayer^ mp;
		GroupBox^ settings;
		CheckBox^ showMovePreviewCheckBox;
		CheckBox^ showTimerCheckBox;
		Button^ loadDataBtn;

		// state components
		AppStates^ as = gcnew AppStates();
		BoardClass^ boardclass = gcnew BoardClass();
		ThemeOptions^ theme = gcnew ThemeOptions();
		Thread^ saver;

		// temporary app states
		bool isSelectingCell = false,
			isMyTrun = false,
			isEnd = false;

		Point lastSelectedCell;

		Generic::Queue<MyFileInfo^>^ filesToSendQueue =
			gcnew Generic::Queue<MyFileInfo^>();


		void InitializeComponent()
		{
			// create window -----------------------------------
			this->Text = L"chess";
			this->Size = DSize(windowWidth, windowHeight);
			this->BackColor = Color::White;

			// roleLabel ---------------------------------------
			roleLabel = gcnew Label();
			roleLabel->Text = gcnew String(
				isServer() ? "server" : "client"
			);
			roleLabel->Location = Point(10, 20);
			roleLabel->AutoSize = true;
			roleLabel->Font = gcnew Drawing::Font(
				L"Guttman-CourMir", 20, FontStyle::Regular, GraphicsUnit::Point, 0);
			this->Controls->Add(roleLabel); // add label to window

			// session id 
			sessionIdLabel = gcnew Label();
			sessionIdLabel->Text = gcnew String(("session id: " + to_string(sessionId)).c_str());
			sessionIdLabel->Location = Point(280, 10);
			sessionIdLabel->AutoSize = true;
			sessionIdLabel->Font = gcnew Drawing::Font(
				L"Guttman-CourMir", 12, FontStyle::Regular, GraphicsUnit::Point, 0);
			this->Controls->Add(sessionIdLabel); // add label to window


			// settings -------------------------------------
			auto settings_font = gcnew System::Drawing::Font(L"Guttman-CourMir", 10, FontStyle::Regular, GraphicsUnit::Point, 0);

			settings = gcnew GroupBox();
			settings->Width = 100;
			settings->AutoSize = true;
			settings->Location = Point(740, 280);

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
			showMovePreviewCheckBox->Click += gcnew EventHandler(this, &GamePage::toggleShowPreview);

			showTimerCheckBox = gcnew CheckBox();
			showTimerCheckBox->AutoSize = true;
			showTimerCheckBox->Location = System::Drawing::Point(0, 430);
			showTimerCheckBox->Text = L"show timer";
			showTimerCheckBox->Font = settings_font;
			showTimerCheckBox->Click += gcnew EventHandler(this, &GamePage::toggleShowTimer);

			loadDataBtn = gcnew Button();
			loadDataBtn->AutoSize = true;
			loadDataBtn->Text = "Load Data";
			loadDataBtn->Font = settings_font;
			loadDataBtn->Location = System::Drawing::Point(0, 460);
			loadDataBtn->Click += gcnew EventHandler(this, &GamePage::loadDataClick);


			// init chess board ---------------------------------
			boardComponent = gcnew ChessBoard(this,
				offsetX, offsetY, 80,
				theme,
				boardclass,
				gcnew Action<Point>(this, &GamePage::OnClickedOnCell)
			);

			// init timer
			timer = gcnew Timerr(this, as, offsetX / 2, offsetY / 2);

			//init music player
			mp = gcnew chessuni::musicPlayer(
				as,
				this,
				gcnew OnNewFileSelectedEvent(this, &GamePage::onNewMusicSelected),
				gcnew OnMusicChangedEvent(this, &GamePage::onMusicChanged),
				gcnew OnPlayStateChangeEvent(this, &GamePage::onPlayStateChanged)
			);
			mp->setOffset(670, 40);

			// add to the page ----------------------------
			settings->Controls->Add(showMovePreviewCheckBox);
			settings->Controls->Add(showTimerCheckBox);
			settings->Controls->Add(loadDataBtn);
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
			SocketInterop::on("game-init", gcnew JsonReciever(this, &GamePage::onGameInit));

			// init enviroment
			as->board = boardclass->board;
			as->selectedTheme = theme;

			if (isServer()) {
				isMyTrun = true;
				saver = gcnew Thread(gcnew ThreadStart(this, &GamePage::saveDataThread));
				saver->Start();

				auto t = gcnew Thread(gcnew ThreadStart(this, &GamePage::serverWorker));
				t->Start();
			}
			else {
				sessionIdLabel->Visible = false;
				settings->Visible = false;
			}

			// prepare UI
			boardComponent->initUI();

			showMovePreviewCheckBox->Checked = as->selectedTheme->showMovePreview;
			showTimerCheckBox->Checked = as->showTimer;

			timer->setVisibility(as->showTimer);
			timer->setTime(30 * 60);
			timer->start();

			mp->initUI();
			mp->setControlVisibility(isServer());

			// add original musics
			auto originalMusicsDir = currentDir() + gcnew String("musics/original/");
			auto files = System::IO::Directory::GetFiles(originalMusicsDir, "*");

			for (int i = 0; i < files->Length; i++)
				mp->addMusic(
					toStdString(System::IO::Path::GetFileName(files[i])),
					toStdString(files[i]));
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			SocketInterop::removeAll();
			timer->stop();
		}
		void loadDataClick(Object^ sender, EventArgs^ e) {
			OpenFileDialog^ ofd = gcnew OpenFileDialog();
			ofd->Multiselect = false;
			ofd->Filter = "JSON Files|*.json";

			if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				auto content = readFile(toStdString(ofd->FileName));
				SocketInterop::sendNtrigger("game-init", json::parse(content));
			}
		}

		// indirect events -------------------------------------------

		// by threads
		void serverWorker() {
			while (true) {
				while (filesToSendQueue->Count) {
					auto fi = filesToSendQueue->Dequeue();
					try
					{
						auto content = base64_encode(readFile(toStdString(fi->path)));
						SocketInterop::send("file", json{
							{"type", "music"},
							{"name", toStdString(fi->name)},
							{"content", content},
							});
					}
					catch (...) {}
				}
				Thread::Sleep(100); // sleep for 0.1s
			}
		}
		void saveDataThread() {
			while (!this->IsDisposed) {
				writeFile(toStdString(DBpath), as->serialize().dump());
				Thread::Sleep(1 * 5 * 1000); // wait for 1 minute
			}
		}

		// board events
		void OnClickedOnCell(Point p) {
			if (!isMyTrun || isEnd) return;

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
					(isServer() && isWhite(boardclass->board[p.Y, p.X])) ||
					(isClient() && isBlack(boardclass->board[p.Y, p.X]))
					)) return;

				isSelectingCell = true;
				lastSelectedCell = p;
				boardclass->movePoints = boardclass->possibleMoves(p);
			}
			boardComponent->render();
		}

		// music player events
		void onMusicChanged(string fname) {
			if (isServer()) {
				as->selectedMusic = gcnew String(fname.c_str());
				setNewSetting();
			}
		}
		void onPlayStateChanged(int stateCode) {
			as->IsMusicPlaying = (stateCode == PLAYING);

			if (isServer())
				setNewSetting();
		}
		void onNewMusicSelected(string fpath, string fname)
		{
			auto fi = gcnew MyFileInfo();
			fi->name = gcnew String(fname.c_str());;
			fi->path = gcnew String(fpath.c_str());;
			filesToSendQueue->Enqueue(fi);
		}

		// theme events
		void onBoardThemeChange(int newColor) {
			theme->boardBackTheme = BoardBackTheme(newColor);
			setNewSetting();
		}
		void onPieceStyleChange(int newColor) {
			theme->pieciesThemeStyle = PieciesThemeStyle(newColor);
			setNewSetting();
		}
		void onPieceColorChange(int newColor) {
			theme->pieciesThemeColor = PieciesThemeColor(newColor);
			setNewSetting();
		}
		void toggleShowPreview(Object^ sender, EventArgs^ e) {
			theme->showMovePreview = showMovePreviewCheckBox->Checked;
			setNewSetting();
		}
		void toggleShowTimer(Object^ sender, EventArgs^ e) {
			as->showTimer = showTimerCheckBox->Checked;
			setNewSetting();
		}

		void setNewSetting() {
			SocketInterop::sendNtrigger("setting", as->serialize());
		}

		// socket events ----------------------------------------------
		void onMove(json data) {
			auto
				p1 = Point(data["from"][0].get<int>(), data["from"][1].get<int>()),
				p2 = Point(data["to"][0].get<int>(), data["to"][1].get<int>());

			boardclass->move(p1, p2);
			boardComponent->render();

			auto gameEndState = boardclass->EndTheGame();
			if (gameEndState == NoOneIsWinner)
				isMyTrun = !isMyTrun;
			else {
				auto winner = (gameEndState == WhiteIsWinner) ? "white" : "black";
				auto winDialog = gcnew WinDialog(gcnew String(winner));
				timer->stop();
				isEnd = true;
				winDialog->ShowDialog();
			}

		}
		void onSettingChange(json data) {
			Console::WriteLine(gcnew String(data.dump().c_str()));
			as->deserialize(data);

			mp->selectMusicByName(as->selectedMusic);
			mp->setPlay(as->IsMusicPlaying);

			this->Invoke(gcnew Action<bool>(timer, &Timerr::setVisibility), as->showTimer);
			showMovePreviewCheckBox->Checked = theme->showMovePreview;

			theme = as->selectedTheme;
			boardclass->board = as->board;
			boardComponent->render();
		}
		void onGameInit(json data) {
			as->deserialize(data);

			timer->setTime(as->restTime);
			onSettingChange(data);
		}
		void onFileRecv(json data) {
			auto
				content = base64_decode(data["content"].get<string>()),
				fname = data["name"].get<string>(),
				fpath = toStdString(currentDir()) + "musics/downloaded/" + fname;

			writeFile(fpath, content);
			mp->addMusic(fname, fpath);
			SocketInterop::send("again", json{});
		}
		void onDisconnect(json data) {}
	};
}