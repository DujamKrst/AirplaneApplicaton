#include "MyForm.h"
#include <stdlib.h>   
#include <ctype.h>
#include <Exception>
#include <complex>
#include <Windows.h>
#include <stdio.h>


using namespace System;


using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Zavrsnirad::MyForm form;
	Application::Run(%form);
	


}