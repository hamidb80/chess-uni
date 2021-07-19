#include "UI/GamePage.h"
#include "UI/MusicPlayer.h"
#include "UI/IntroPage.h"
#include "UI/WaitRoom.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(){
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	
	UI::IntroPage inp;
	Application::Run(% inp);

	if (*UI::userRole == UI::ServerRole)
		appSocket = new SocketServer();
	else
		appSocket = new SocketClient();
	
	SocketInterop::run();

	UI::WaitRoom waitForm;
	Application::Run(% waitForm);

	UI::GamePage form;
	Application::Run(% form);
}