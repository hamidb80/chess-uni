#pragma once

#include<string>
#include<json.hpp>
using std::string;
using json = nlohmann::json;

#include "../modules/socketio.hpp"

namespace UI {
	using namespace System;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class WaitRoom : public System::Windows::Forms::Form
	{
	public:
		int counter = 0;
		WaitRoom(void)
		{
			InitializeComponent();
		}
		~WaitRoom()
		{
			if (components)
				delete components;
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		Thread^ timerThread;

	private: System::Windows::Forms::ColorDialog^ colorDialog1;
		   bool isActive = true;


#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(550, 68);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(269, 55);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"Please wait";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->ForeColor = System::Drawing::Color::DimGray;
			   this->label2->Location = System::Drawing::Point(465, 153);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(453, 36);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"[waiting for other side to connect]";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label3->Location = System::Drawing::Point(837, 68);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(63, 55);
			   this->label3->TabIndex = 2;
			   this->label3->Text = L"...";
			   // 
			   // WaitRoom
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1370, 462);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Name = L"WaitRoom";
			   this->Text = L"Wait Room";
			   this->Load += gcnew System::EventHandler(this, &WaitRoom::MyForm_Load);
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private:
		void onConnect(json data) {
			Console::WriteLine("connected");
			SocketInterop::remove("connect");
			this->isActive = false;
			this->Invoke(gcnew Action(this, &WaitRoom::Close)); // close via another thread
		}

		Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->timerThread = gcnew Thread(gcnew ThreadStart(this, &WaitRoom::loop));
			this->timerThread->Start();

			SocketInterop::on("connect", gcnew JsonReciever(this, &WaitRoom::onConnect));
		}
		Void updateLoading() {
			string s = "";
			for (int i = 0; i <= counter; i++)
				s += ".";

			label3->Text = gcnew String(s.c_str());
		}
		Void loop() {
			while (this->isActive) {
				this->Invoke(gcnew Action(this, &WaitRoom::updateLoading));

				counter++;
				if (counter == 3) counter = 0;

				Thread::Sleep(1000); // wait for 1 second [ 1000 ms ]
			}
		}
		Void onClosingForm(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			isActive = false;
			this->timerThread->Join();
		}
	};
}
