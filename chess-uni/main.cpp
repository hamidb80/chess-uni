#include "UI/game.h"

using namespace System;
using namespace System::Windows::Forms;

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	UI::MyForm frm;
	Application::Run(% frm);
}
