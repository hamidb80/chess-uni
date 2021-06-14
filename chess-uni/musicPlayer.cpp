#include "musicPlayer.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
Void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project1::musicPlayer form;
	Application::Run(% form);

}

