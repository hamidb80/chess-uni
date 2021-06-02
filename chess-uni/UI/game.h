#pragma once
#include "timer.h"

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	public ref class GamePage : public Form
	{
	public:
		GamePage(void)
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

		array<Button^>^ boardBtns = gcnew array<Button^>(64);
		Timer^ timer;

		void InitializeComponent(void)
		{
			// create window
			this->AutoScaleDimensions = SizeF(14, 29);
			this->ClientSize = DSize(800, 600);
			this->Text = L"main windows";

			// create chess board
			int
				size = 50,
				offsetY = 100,
				offsetX = 100;

			for (int y = 0; y < 8; y++)
				for (int x = 0; x < 8; x++) {
					auto btn = boardBtns[y * 8 + x] = gcnew Button();

					btn->Location = Point(offsetY + size * y, offsetX + size * x);
					btn->Size = DSize(size, size);
					btn->Text = L"btn1";
					btn->UseVisualStyleBackColor = true;

					this->Controls->Add(btn);
				}

			// create timer
			timer = gcnew UI::Timer(this, offsetX / 2, offsetY / 2);
			timer->setTime(5 * 60 * 60);

			// set form events
			this->Load += gcnew EventHandler(this, &GamePage::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &GamePage::OnClosed);
		}
		void OnLoad(Object^ sender, EventArgs^ e) {
			timer->start();
		}
		void OnClosed(Object^ sender, FormClosingEventArgs^ e) {
			timer->stop();
		}
	};
}
