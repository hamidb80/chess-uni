#pragma once

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class WinDialog : public Form
	{
	public:
		WinDialog(String^ _winner)
		{
			InitializeComponent(_winner);
		}
		~WinDialog()
		{
			if (components)
				delete components;
		}
	
	private:
		Button^ ok_button;
		Label^ label1;
		System::ComponentModel::Container^ components;
	
		void InitializeComponent(String^ _winner)
		{
			this->ok_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// ok_button
			// 
			this->ok_button->Location = System::Drawing::Point(216, 238);
			this->ok_button->Name = L"ok_button";
			this->ok_button->Size = System::Drawing::Size(194, 61);
			this->ok_button->TabIndex = 0;
			this->ok_button->Text = L"OK";
			this->ok_button->UseVisualStyleBackColor = true;
			this->ok_button->Click += gcnew System::EventHandler(this, &WinDialog::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(251, 84);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(132, 48);
			this->label1->TabIndex = 1;
			this->label1->Text = _winner + " Won!";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(14, 29);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(652, 385);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ok_button);
			this->Name = L"win_dialog";
			this->Text = L"win dialog";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
	
	private:
		Void button1_Click(Object^ sender, EventArgs^ e) {
			this->Close();
		}
	};
}
