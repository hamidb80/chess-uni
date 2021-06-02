#pragma once

#include <string>
using std::to_string;

namespace chessuni {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using System::Windows::Forms::Button;
	using System::Windows::Forms::Label;
	using System::Drawing::Point;
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
		/// Required designer variable.
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
		array<Button^>^ boardBtns = gcnew array<Button^>(64);

		Thread^ timerThread;
		Label^ timer = gcnew Label();

		void startTimer() {
			int a = 10;
			while (true) {
				Thread::Sleep(1000);
				auto newText = gcnew String(to_string(a--).c_str());
				//this->Invoke(this->timer);
			}
		}

		void RuntimeDesigner() {
			// create btns
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
			timer->Text = "00:01:00";
			timer->Location = Point(offsetY / 2, offsetX / 2);
			timer->AutoSize = true;
			this->Controls->Add(timer);

			this->timerThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::startTimer));
			this->timerThread->Start();
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1056, 1266);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
		{
			this->ClientSize = System::Drawing::Size(800, 600);
			this->RuntimeDesigner();
		}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
