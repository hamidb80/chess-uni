#pragma once
#include"../modules/database.h"

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	// 1 => "01" , 12 => "12"
	String^ TimeFormated(int num) {
		if (num >= 10)
			return num.ToString();
		else {
			auto s = L"0" + num.ToString();
			return s;
		}
	}
	// 75 => "00:01:15"
	String^ secondsToTime(int secs) {
		int
			sec = secs % 60,
			min = (secs % 3600) / 60,
			hour = secs / 3600;

		return
			TimeFormated(hour) + ":" +
			TimeFormated(min) + ":" +
			TimeFormated(sec);
	}


	public ref class Timerr
	{
	private:
		Form^ mainForm;
		bool isActive = false;

		Thread^ timerThread;
		Label^ timerLable = gcnew Label();
		int currentTime = 0; // per seconds

		AppStates^ as;

		void updateTimeText() {
			as->restTime = currentTime;
			timerLable->Text = secondsToTime(currentTime);
		}

	public:
		Timerr(Form^ mf, AppStates^ _as, int offsetX, int offsetY)
		{
			this->as = _as;
			this->mainForm = mf;

			// add style to label
			timerLable->Location = Point(offsetX, offsetY);
			timerLable->AutoSize = true;
			timerLable->Font = gcnew Font(
				L"Guttman-CourMir", 20, FontStyle::Regular, GraphicsUnit::Point, 0);

			// add label to window
			mf->Controls->Add(timerLable);
		}

		void setVisibility(bool isVisible) {
			timerLable->Visible = isVisible;
		}
		void setTime(int secs) { // set currentTime to ginen time (secs: per seconds]
			currentTime = secs;
			updateTimeText();
		}
		void start() {
			isActive = true;

			// start timer thread [ it decreases time every seconds ]
			this->timerThread = gcnew Thread(gcnew ThreadStart(this, &Timerr::loop));
			this->timerThread->Start();
		}
		void stop() {
			isActive = false;
		}
		void reset() {
			currentTime = 0;
		}
		void loop() {
			while (true) {
				if (!isActive) return;

				try // i dont know why that ridicouless error happens
				{
					mainForm->Invoke(gcnew Action(this, &Timerr::updateTimeText));

					if (currentTime != 0)
						currentTime--;
					else
						return; // end the function [ whick causes thread to die ]
				}
				catch (...) { return; }

				Thread::Sleep(1000); // wait for 1 second [ 1000 ms ]
			}
		}
	};
};