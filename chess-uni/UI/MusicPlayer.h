#pragma once
namespace chessuni {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;
   #define yMusic 500
   #define xMusic 35

	/// <summary>
	/// Summary for musicPlayer
	/// </summary>
	public ref class musicPlayer
	{
	public:
		Control::ControlCollection^ Controls;
		musicPlayer(Control::ControlCollection^ cntrl)
		{
			Controls = cntrl;
			InitializeComponent();
		}

		void pause() {
			axWindowsMediaPlayer1->Ctlcontrols->pause();
		}
		void play() {}
		void hide() {
			axWindowsMediaPlayer1->Visible = false;
		}
		void show() {}

	protected:
		~musicPlayer()
		{
			if (components)
				delete components;
		}
	private: AxWMPLib::AxWindowsMediaPlayer^ axWindowsMediaPlayer1;
	private: System::Windows::Forms::Panel^ panel1;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnSelectSongs;
	private: System::Windows::Forms::ListBox^ listBoxSongs;
	private: System::Windows::Forms::Label^ lblLogo;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(musicPlayer::typeid));
			this->axWindowsMediaPlayer1 = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->lblLogo = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnSelectSongs = (gcnew System::Windows::Forms::Button());
			this->listBoxSongs = (gcnew System::Windows::Forms::ListBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			// 
			// axWindowsMediaPlayer1
			// 
			this->axWindowsMediaPlayer1->Enabled = true;
			this->axWindowsMediaPlayer1->Location = System::Drawing::Point(2+xMusic, 51+yMusic); //2 , 51
			this->axWindowsMediaPlayer1->Name = L"axWindowsMediaPlayer1";
			this->axWindowsMediaPlayer1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer1.OcxState")));
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(523, 45);
			this->axWindowsMediaPlayer1->TabIndex = 0;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::DarkTurquoise;
			this->panel1->Controls->Add(this->lblLogo);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(2+xMusic, 4+yMusic);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(523, 42);
			this->panel1->TabIndex = 1;
			// 
			// lblLogo
			// 
			this->lblLogo->AutoSize = true;
			this->lblLogo->Font = (gcnew System::Drawing::Font(L"Stylus BT", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblLogo->Location = System::Drawing::Point(55+xMusic, 8+yMusic);
			this->lblLogo->Name = L"lblLogo";
			this->lblLogo->Size = System::Drawing::Size(58, 23);
			this->lblLogo->TabIndex = 6;
			this->lblLogo->Text = L"Music";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(3+xMusic, 2+yMusic);
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
			this->btnSelectSongs->Location = System::Drawing::Point(529+xMusic, 75+yMusic);
			this->btnSelectSongs->Name = L"btnSelectSongs";
			this->btnSelectSongs->Size = System::Drawing::Size(120, 23);
			this->btnSelectSongs->TabIndex = 3;
			this->btnSelectSongs->Text = L"Select Songs";
			this->btnSelectSongs->UseVisualStyleBackColor = false;
			this->btnSelectSongs->Click += gcnew System::EventHandler(this, &musicPlayer::BtnSelectSongs_Click);
			// 
			// listBoxSongs
			// 
			this->listBoxSongs->FormattingEnabled = true;
			this->listBoxSongs->Location = System::Drawing::Point(529+xMusic, 2+yMusic);
			this->listBoxSongs->Name = L"listBoxSongs";
			this->listBoxSongs->Size = System::Drawing::Size(120, 69);
			this->listBoxSongs->TabIndex = 4;
			this->listBoxSongs->SelectedIndexChanged += gcnew System::EventHandler(this, &musicPlayer::ListBoxSongs_SelectedIndexChanged);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// musicPlayer
			// 

			this->Controls->Add(this->listBoxSongs);
			this->Controls->Add(this->btnSelectSongs);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->axWindowsMediaPlayer1);
			this->axWindowsMediaPlayer1->BringToFront();

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		}
#pragma endregion
		array< String^ >^ fileName = gcnew array< String^ >(10);
		array< String^ >^ paths = gcnew array< String^ >(10);

	private:
		System::Void BtnSelectSongs_Click(System::Object^ sender, System::EventArgs^ e) {

			OpenFileDialog ofd;
			ofd.Multiselect = true;
			ofd.Filter = "MP3 Files|*.mp3|MP4 Files|*.mp4 | WAV Files|*.wav | WMA Files |*.WMA ";

			//openFileDialog1->Title = "Select Music";
			//openFileDialog1->Filter = "MP3 files (*.mp3)|*.mp3|MP4 files (*.mp4)|*.mp4|WAV files (*.WAV)|*.WAV|WMA files (*.wma)|*.wma";
			//openFileDialog1->Multiselect = false;

			if (ofd.ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				fileName = ofd.SafeFileNames; // save the name of track in filename array
				paths = ofd.FileNames; // save the paths of the tracks in path array
				for (int i = 0; i < fileName->Length; i++)
				{
					listBoxSongs->Items->Add(fileName[i]);
				}


			}
			else
			{
			}




		}
		System::Void ListBoxSongs_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			axWindowsMediaPlayer1->URL = paths[listBoxSongs->SelectedIndex];
		}
	};
}
