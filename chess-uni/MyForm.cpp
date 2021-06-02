#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;

void main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	chessuni::MyForm frm;
	Application::Run(% frm);
}
