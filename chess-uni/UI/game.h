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

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}
		~MyForm()
		{
			if (components)
				delete components;
		}

	private:
		System::ComponentModel::IContainer^ components;
		
		array<Button^>^ boardBtns = gcnew array<Button^>(64);
		Timer^ timer;

		void InitializeComponent(void)
		{
			// create window
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 600);
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
			timer->start();
		}
	};
}
