#include "UI/GamePage.h"
#include "UI/MusicPlayer.h"
#include "UI/IntroPage.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(){
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	
	UI::IntroPage inp;
	Application::Run(% inp);

	if (UI::isServer)
		appSocket = new SocketServer();
	else
		appSocket = new SocketClient();
	
	UI::GamePage form;
	Application::Run(% form);
}