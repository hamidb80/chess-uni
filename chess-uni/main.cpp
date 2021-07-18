#include "UI/GamePage.h"
#include "UI/MusicPlayer.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(){
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	UI::GamePage frm;
	Application::Run(% frm);
}