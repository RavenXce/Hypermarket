// Hypermarket.cpp : main project file.

#include "stdafx.h"
#include "Hypermarket.h"

using namespace Hypermarket;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	
	int next;
	string curUser;
	Inventory *inv = new Inventory();
	Password *pwdatabase = new Password();
	Application::Run(gcnew LoginMenu(&next,&curUser,pwdatabase));		
	while(next){
		switch(next){
			case 1: next = 0; Application::Run(gcnew CashierUI(&next,&curUser,inv,pwdatabase)); break;
			case 2: next = 0; Application::Run(gcnew ManagerUI(&next,&curUser,inv,pwdatabase)); break;
			case 3: next = 0; Application::Run(gcnew LoginMenu(&next,&curUser,pwdatabase)); break;
			default: next = 0; break;
		}
	}
	delete inv;
	delete pwdatabase;
	return 0;
}