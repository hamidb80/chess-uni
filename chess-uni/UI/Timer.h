#pragma once

namespace UI {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using DSize = System::Drawing::Size;

	// 1 => 01 , 12 => 12
	String^ TimeFormated(int num) {
		if (num >= 10)
			return num.ToString();
		else {
			auto s = L"0" + num.ToString();
			return s;
		}
	}

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

	public ref class Timer
	{
	private:
		Form^ mainForm;
		bool isActive = false;

		Thread^ timerThread;
		Label^ timer = gcnew Label();
		int currentTime = 0;

	public:
		Timer(Form^ mf, int offsetY, int offsetX)
		{
			this->mainForm = mf;

			timer->Location = Point(offsetY, offsetX);
			timer->AutoSize = true;
			mf->Controls->Add(timer);
		}
		~Timer() {	}

		void start() {
			isActive = true;
			
			this->timerThread = gcnew Thread(gcnew ThreadStart(this, &Timer::loop));
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
				if (!isActive)
					return;

				if (currentTime != -1) {
					mainForm->Invoke(gcnew Action(this, &Timer::updateTimeText));
					currentTime--;
				}

				Thread::Sleep(1000);
			}
		}

		void setTime(int secs) {
			currentTime = secs;
			updateTimeText();
		}
		void updateTimeText() {
			this->timer->Text = secondsToTime(currentTime);
		}
	};
};