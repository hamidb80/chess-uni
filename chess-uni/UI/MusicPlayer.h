#pragma once
#pragma once

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	public ref class MusicPlayer : public System::Windows::Forms::Form
	{
	private:
		Form^ mainForm;
		System::ComponentModel::Container^ components;

		SoundPlayer^ player;
		Button^ playbtn;
		Button^ stopBtn;


	public:
		MusicPlayer(Form^ mf, int offsetX, int offsetY)
		{
			mainForm = mf;

			this->player = gcnew System::Media::SoundPlayer();
			player->SoundLocation = "C:\\Users\\HamidB80\\Music\\PinkPanther60.wav";
			player->Load();

			playbtn = gcnew Button();
			playbtn->Location = Point(offsetX + 33, offsetY);
			playbtn->Click += gcnew EventHandler(this, &MusicPlayer::play);
			playbtn->Text = "play";
			this->mainForm->Controls->Add(playbtn);

			stopBtn = gcnew Button();
			stopBtn->Location = Point(offsetX + 100, offsetY);
			stopBtn->Text = "stop";
			stopBtn->Click += gcnew EventHandler(this, &MusicPlayer::stop);
			this->mainForm->Controls->Add(stopBtn);
		}

		~MusicPlayer()
		{
			if (components)
				delete components;
		}

	public:
		void play(Object^ sender, EventArgs^ e) {
			player->PlayLooping();
		}
		void stop(Object^ sender, EventArgs^ e) {
			player->Stop();
		}
	};
}
