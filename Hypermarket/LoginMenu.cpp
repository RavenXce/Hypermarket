#include "stdafx.h"
#include "LoginMenu.h"

using namespace Hypermarket;
void LoginMenu::loginbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	int index = typeBox->SelectedIndex;
	string userID = Wrapper::toUnmanagedString(idBox->Text->ToString());
	string pw = Wrapper::toUnmanagedString(pwBox->Text->ToString());
	if(_pwdatabase->log_in(index,userID,pw)){
		*_next = typeBox->SelectedIndex + 1;
		*_curUser = userID;
		this->Close();
	}
	else (MessageBox::Show(
		"Invalid UserID or password!\nPlease check account details and domain name.", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error));
}
void LoginMenu::LoginMenu_Load(System::Object^  sender, System::EventArgs^  e) {				 
	if(!_pwdatabase->load_pw_data("accounts.txt")){
		MessageBox::Show(
			"Unable to load account database!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		MessageBox::Show(
			"Creating default database... Please login with the default userID and password.", 
			"Warning", MessageBoxButtons::OK, MessageBoxIcon::Information);					 
		_pwdatabase->add_account(1,"admin","password");
		_pwdatabase->save_pw_data("accounts.txt");
	}
	typeBox->SelectedIndex = 0;
}
void LoginMenu::idBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ( e->KeyChar == (char)13 ){ // enter key hit					
		pwBox->Focus();
		e->Handled = true;
	}
}
void LoginMenu::pwBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ( e->KeyChar == (char)13 ){ // enter key hit
		if(typeBox->SelectedIndex==-1) typeBox->Focus();
		else loginbtn->PerformClick();
		e->Handled = true;
	}			 
}
void LoginMenu::typeBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ( e->KeyChar == (char)13 ){ // enter key hit
		if(typeBox->SelectedIndex==-1) loginbtn->Focus();
		else loginbtn->PerformClick();
		e->Handled = true;
	}	
}
void LoginMenu::idBox_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (!System::String::IsNullOrEmpty(idBox->Text))
	{
		idBox->SelectionStart = 0;
		idBox->SelectionLength = idBox->Text->Length;
	}
}
void LoginMenu::pwBox_Enter(System::Object^  sender, System::EventArgs^  e) {
	if (!System::String::IsNullOrEmpty(pwBox->Text))
	{
		pwBox->SelectionStart = 0;
		pwBox->SelectionLength = pwBox->Text->Length;
	}
}