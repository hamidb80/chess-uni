#pragma once

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	enum UserRoles {
		NotSetRole,
		ServerRole,
		ClientRole,
	};
	UserRoles* userRole = new UserRoles(NotSetRole);

	bool isServer() {
		return *UI::userRole == ServerRole;
	}
	bool isClient() {
		return *UI::userRole == ClientRole;
	}


	public ref class IntroPage : public System::Windows::Forms::Form
	{
	public:
		IntroPage(void)
		{
			InitializeComponent();
		}

	protected:
		~IntroPage()
		{
			if (components)
				delete components;
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;


	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderSize = 2;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(404, 139);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(435, 111);
			this->button1->TabIndex = 0;
			this->button1->Text = L"server";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &IntroPage::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(404, 280);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(435, 111);
			this->button2->TabIndex = 1;
			this->button2->Text = L"client";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &IntroPage::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(507, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(271, 40);
			this->label1->TabIndex = 2;
			this->label1->Text = L"select  your role";
			// 
			// IntroPage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1210, 440);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"IntroPage";
			this->Text = L"Intro";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	private:
		Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			*userRole = ServerRole;
			this->Close();
		}
		Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			*userRole = ClientRole;
			this->Close();
		}
	
};
}
