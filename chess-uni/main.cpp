#include "UI/GamePage.h"
#include "UI/MusicPlayer.h"
#include "UI/IntroPage.h"
#include "UI/WaitRoom.h"

using namespace System;
using namespace System::Windows::Forms;

void run() {
	//Application::SetCompatibleTextRenderingDefault(false);
	//Application::EnableVisualStyles();

	//UI::IntroPage inp;
	//Application::Run(% inp);

	//if (*UI::userRole == UI::ServerRole)
	//	appSocket = new SocketServer();
	//else if (*UI::userRole == UI::ClientRole)
	//	appSocket = new SocketClient();
	//else 
	//	return;

	//SocketInterop::run(); 

	//UI::WaitRoom waitForm;
	//Application::Run(% waitForm);

	//if (*UI::isCanceled) return;

	* UI::userRole = UI::ServerRole;

	UI::GamePage form;
	Application::Run(% form);
}

[STAThreadAttribute]
void main() {
	run();
	System::Diagnostics::Process::GetCurrentProcess()->Kill(); // to close all threads
}