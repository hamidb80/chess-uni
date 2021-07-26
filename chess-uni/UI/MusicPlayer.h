#pragma once
#include "../modules/database.h"
#include "../modules/socketio.hpp"

delegate void OnNewFileSelectedEvent(string fpath, string fname);
delegate void OnMusicChangedEvent(string fname);
delegate void OnPlayStateChangeEvent(int stateCode);

const int
STOPPED = 1,
PAUSED = 2,
PLAYING = 3;

namespace chessuni {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;

	public ref class musicPlayer
	{
		AppStates^ as;
		Control::ControlCollection^ Controls;
		OnNewFileSelectedEvent^ onse;
		OnMusicChangedEvent^ omc;
		OnPlayStateChangeEvent^ opsc;
		int lastSelectedMusicIndex = -1;

	public:
		musicPlayer(
			AppStates^ _apst,
			Control::ControlCollection^ cntrl,
			OnNewFileSelectedEvent^ _nse,
			OnMusicChangedEvent^ _om,
			OnPlayStateChangeEvent^ _opsc
		)
		{
			opsc = _opsc;
			onse = _nse;
			omc = _om;
			as = _apst;
			Controls = cntrl;
			InitializeComponent();
		}

		List<String^>^ names = gcnew List<String^>();
		List<String^>^ paths = gcnew List<String^>();

		void Play()
		{
			if (!isPlaying())
				axWindowsMediaPlayer1->Ctlcontrols->play();
		}
		void Pause()
		{
			if (isPlaying())
				axWindowsMediaPlayer1->Ctlcontrols->pause();
		}
		void setPlay(bool play) {
			if (play)
				Play();
			else
				Pause();
		}
		bool isPlaying() {
			return axWindowsMediaPlayer1->playState == WMPLib::WMPPlayState::wmppsPlaying;
		}
		void initUI()
		{
			this->axWindowsMediaPlayer1->uiMode = "none";
		}
		void setControlVisibility(bool isVisible) {
			this->btnPlayPause->Visible = isVisible;
			this->btnSelectSongs->Visible = isVisible;
		}

		void setOffset(int offx, int offy) {
			groupBoxMusic->Location = Point(offx, offy);
		}
		void addMusic(string fname, string fpath) {
			auto path = gcnew String(fpath.c_str());
			auto name = gcnew String(fname.c_str());

			paths->Add(path);
			names->Add(name);
			listBoxSongs->Items->Add(name);
		}
		void selectMusicByIndex(int index) {
			if (index == lastSelectedMusicIndex) return; // avoid replay

			auto p = paths[index];

			if (System::IO::File::Exists(p))
				axWindowsMediaPlayer1->URL = p;

			lastSelectedMusicIndex = index;
		}
		void selectMusicByName(String^ name) {
			for (int i = 0; i < names->Count; i++)
				if (name == names[i])
					return selectMusicByIndex(i);
		}

		// https://docs.microsoft.com/en-us/windows/win32/wmp/axwindowsmediaplayer-object--vb-and-c

	private: System::ComponentModel::IContainer^ components;

	private: AxWMPLib::AxWindowsMediaPlayer^ axWindowsMediaPlayer1;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnSelectSongs;
	private: System::Windows::Forms::ListBox^ listBoxSongs;
	private: System::Windows::Forms::Label^ lblLogo;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::GroupBox^ groupBoxMusic;

	private: System::Windows::Forms::Button^ btnPlayPause;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(musicPlayer::typeid));
			   this->axWindowsMediaPlayer1 = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->lblLogo = (gcnew System::Windows::Forms::Label());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnSelectSongs = (gcnew System::Windows::Forms::Button());
			   this->btnPlayPause = (gcnew System::Windows::Forms::Button());
			   this->listBoxSongs = (gcnew System::Windows::Forms::ListBox());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   this->groupBoxMusic = (gcnew System::Windows::Forms::GroupBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->BeginInit();
			   this->panel1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->groupBoxMusic->SuspendLayout();
			   // 
			   // axWindowsMediaPlayer1
			   // 
			   this->axWindowsMediaPlayer1->Enabled = true;
			   this->axWindowsMediaPlayer1->Location = System::Drawing::Point(6, 151);
			   this->axWindowsMediaPlayer1->Name = L"axWindowsMediaPlayer1";
			   this->axWindowsMediaPlayer1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer1.OcxState")));
			   this->axWindowsMediaPlayer1->Size = System::Drawing::Size(227, 45);
			   this->axWindowsMediaPlayer1->TabIndex = 0;
			   this->axWindowsMediaPlayer1->PlayStateChange += gcnew AxWMPLib::_WMPOCXEvents_PlayStateChangeEventHandler(this, &musicPlayer::onStatusChanged);
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::Color::DarkTurquoise;
			   this->panel1->Controls->Add(this->lblLogo);
			   this->panel1->Controls->Add(this->pictureBox1);
			   this->panel1->Location = System::Drawing::Point(6, 0);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(227, 42);
			   this->panel1->TabIndex = 1;
			   // 
			   // lblLogo
			   // 
			   this->lblLogo->AutoSize = true;
			   this->lblLogo->Font = (gcnew System::Drawing::Font(L"Stylus BT", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->lblLogo->Location = System::Drawing::Point(55, 8);
			   this->lblLogo->Name = L"lblLogo";
			   this->lblLogo->Size = System::Drawing::Size(58, 23);
			   this->lblLogo->TabIndex = 6;
			   this->lblLogo->Text = L"Music";
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			   this->pictureBox1->Location = System::Drawing::Point(3, 2);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(49, 39);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->pictureBox1->TabIndex = 5;
			   this->pictureBox1->TabStop = false;
			   // 
			   // btnSelectSongs
			   // 
			   this->btnSelectSongs->BackColor = System::Drawing::Color::PeachPuff;
			   this->btnSelectSongs->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnSelectSongs->ForeColor = System::Drawing::Color::SaddleBrown;
			   this->btnSelectSongs->Location = System::Drawing::Point(6, 122);
			   this->btnSelectSongs->Name = L"btnSelectSongs";
			   this->btnSelectSongs->Size = System::Drawing::Size(227, 23);
			   this->btnSelectSongs->TabIndex = 3;
			   this->btnSelectSongs->Text = L"Select Songs";
			   this->btnSelectSongs->UseVisualStyleBackColor = false;
			   this->btnSelectSongs->Click += gcnew System::EventHandler(this, &musicPlayer::BtnSelectSongs_Click);
			   // 
			   // listBoxSongs
			   // 
			   this->listBoxSongs->FormattingEnabled = true;
			   this->listBoxSongs->Location = System::Drawing::Point(6, 47);
			   this->listBoxSongs->Name = L"listBoxSongs";
			   this->listBoxSongs->Size = System::Drawing::Size(227, 69);
			   this->listBoxSongs->TabIndex = 4;
			   this->listBoxSongs->SelectedIndexChanged += gcnew System::EventHandler(this, &musicPlayer::ListBoxSongs_SelectedIndexChanged);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // groupBoxMusic
			   // 
			   this->groupBoxMusic->BackColor = System::Drawing::Color::OldLace;
			   this->groupBoxMusic->Controls->Add(this->panel1);
			   this->groupBoxMusic->Controls->Add(this->listBoxSongs);
			   this->groupBoxMusic->Controls->Add(this->axWindowsMediaPlayer1);
			   this->groupBoxMusic->Controls->Add(this->btnSelectSongs);
			   this->groupBoxMusic->Location = System::Drawing::Point(0, 27);
			   this->groupBoxMusic->Name = L"groupBoxMusic";
			   this->groupBoxMusic->Size = System::Drawing::Size(239, 230);
			   this->groupBoxMusic->TabIndex = 2;
			   this->groupBoxMusic->TabStop = false;
			   //
			   // btn play pause
			   // 
			   this->btnPlayPause->BackColor = System::Drawing::Color::PeachPuff;
			   this->btnPlayPause->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnPlayPause->ForeColor = System::Drawing::Color::SaddleBrown;
			   this->btnPlayPause->Location = Point(6, 200);
			   this->btnPlayPause->TabIndex = 3;
			   this->btnPlayPause->Text = L"play / pause";
			   this->btnPlayPause->UseVisualStyleBackColor = false;
			   this->btnPlayPause->Size = DSize(227, 23);
			   this->btnPlayPause->Click += gcnew System::EventHandler(this, &musicPlayer::playPauseHandlre);
			   // 
			   // musicPlayer
			   // 
			   groupBoxMusic->Controls->Add(this->btnPlayPause);
			   this->Controls->Add(this->groupBoxMusic);

			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->EndInit();
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->groupBoxMusic->ResumeLayout(false);
		   }
#pragma endregion

	private:
		void BtnSelectSongs_Click(Object^ sender, EventArgs^ e) {

			OpenFileDialog ofd;
			ofd.Multiselect = true;
			ofd.Filter = "MP3 Files|*.mp3|MP4 Files|*.mp4 | WAV Files|*.wav | WMA Files |*.WMA ";

			if (ofd.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				for (int i = 0; i < ofd.FileNames->Length; i++) {
					// add to music list
					addMusic(toStdString(ofd.SafeFileNames[i]), toStdString(ofd.FileNames[i]));

					// trigger event handler
					onse(toStdString(ofd.FileNames[i]), toStdString(ofd.SafeFileNames[i]));
				}
			}
		}
		void ListBoxSongs_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
			if (listBoxSongs->SelectedIndex != -1) {
				omc(toStdString(names[listBoxSongs->SelectedIndex]));
				selectMusicByIndex(listBoxSongs->SelectedIndex);
			}
		}
		void onStatusChanged(Object^ sender, AxWMPLib::_WMPOCXEvents_PlayStateChangeEvent^ e) {

			if (e->newState == PLAYING || e->newState == PAUSED)
				opsc(e->newState);

			else if (e->newState == STOPPED)
				if (as->IsMusicPlaying)
					this->Play();
		}
		void playPauseHandlre(Object^ sender, EventArgs^ e) {
			if (isPlaying())
				Pause();
			else
				Play();
		}
	};
}
