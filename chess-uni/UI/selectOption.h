#pragma once
#include<string>
#include"../utils/lambda.h"

using namespace std;

generic<class T>
	delegate void ClickEvent(T a);

	namespace UI {
		using namespace System;
		using namespace System::ComponentModel;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;
		using namespace System::Threading;
		using namespace System::Collections::Generic;
		using DSize = System::Drawing::Size;

		public ref class SelectOption
		{
		private:
			List<Button^>^ btns = gcnew List<Button^>();
			GroupBox^ group = gcnew GroupBox();

			Font^ font;
			int width, height;
		public:
			SelectOption(
				Control::ControlCollection^ cntrl,
				string title,
				Font^ fnt,
				int wid, int ht,
				int offsetX, int offsetY) :
				font(fnt), width(wid), height(ht)
			{
				auto lb = gcnew Label();
				lb->Text = gcnew String(title.c_str());
				lb->Font = font;
				lb->Width = width;
				lb->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

				group->Controls->Add(lb);
				group->Location = Point(offsetX, offsetY);
				group->Width = width;
				group->Height = lb->Height;
				cntrl->Add(group);
			}
			generic<class T>
				void addOption(string text, T val, Action<T>^ whenClicked) {

					auto btn = gcnew Button();

					// add style to button
					btn->Location = Point();
					btn->Size = DSize(width, height);
					btn->Font = font;
					btn->FlatAppearance->BorderSize = 1;
					btn->FlatStyle = FlatStyle::Flat;
					btn->Text = gcnew String(text.c_str());
					btn->Location = Point(0, group->Height);

					// add click event
					auto lw = gcnew UiEventLambdaWrapper<T>();
					lw->valToPass = val;
					lw->nextFunc = whenClicked;
					btn->Click += gcnew EventHandler(lw, &UiEventLambdaWrapper<T>::func);

					// add button to window
					group->Controls->Add(btn);
					group->Height += height;
					btns->Add(btn);
				}
		};
	};