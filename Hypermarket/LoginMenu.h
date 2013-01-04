#pragma once
#include "password.h"
#include "wrapper.h"

namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoginMenu
	/// </summary>
	public ref class LoginMenu : public System::Windows::Forms::Form
	{
	public:
		LoginMenu(int* next, string* curUser, Password* pwDB)
		{
			_next = next;
			_curUser = curUser;
			_pwdatabase = pwDB;
			StartPosition = FormStartPosition::CenterScreen;
			InitializeComponent();	
		}		

	protected:
		~LoginMenu()
		{
			if (components)
			{
				delete components;
			}
		}

	
		int *_next;
		string* _curUser;
		Password* _pwdatabase;			
		System::ComponentModel::Container ^components;

#pragma region WindowsFormDeclarationRegion

	 System::Windows::Forms::Label^  label1;
	 System::Windows::Forms::Label^  label2;
	 System::Windows::Forms::TextBox^  idBox;
	 System::Windows::Forms::ComboBox^  typeBox;
	 System::Windows::Forms::Label^  label3;
	 System::Windows::Forms::Button^  loginbtn;
	 System::Windows::Forms::MaskedTextBox^  pwBox;

#pragma endregion
#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->idBox = (gcnew System::Windows::Forms::TextBox());
				 this->typeBox = (gcnew System::Windows::Forms::ComboBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->loginbtn = (gcnew System::Windows::Forms::Button());
				 this->pwBox = (gcnew System::Windows::Forms::MaskedTextBox());
				 this->SuspendLayout();
				 // 
				 // label1
				 // 
				 this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(90, 37);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(40, 13);
				 this->label1->TabIndex = 0;
				 this->label1->Text = L"UserID";
				 // 
				 // label2
				 // 
				 this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(90, 77);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(53, 13);
				 this->label2->TabIndex = 1;
				 this->label2->Text = L"Password";
				 // 
				 // idBox
				 // 
				 this->idBox->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->idBox->Location = System::Drawing::Point(159, 34);
				 this->idBox->Name = L"idBox";
				 this->idBox->Size = System::Drawing::Size(178, 20);
				 this->idBox->TabIndex = 0;
				 this->idBox->Enter += gcnew System::EventHandler(this, &LoginMenu::idBox_Enter);
				 this->idBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &LoginMenu::idBox_KeyPress);
				 // 
				 // typeBox
				 // 
				 this->typeBox->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->typeBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->typeBox->FormattingEnabled = true;
				 this->typeBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Cashier", L"Manager"});
				 this->typeBox->Location = System::Drawing::Point(159, 115);
				 this->typeBox->Name = L"typeBox";
				 this->typeBox->Size = System::Drawing::Size(178, 21);
				 this->typeBox->TabIndex = 2;
				 this->typeBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &LoginMenu::typeBox_KeyPress);
				 // 
				 // label3
				 // 
				 this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(90, 118);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(48, 13);
				 this->label3->TabIndex = 5;
				 this->label3->Text = L"Login As";
				 // 
				 // loginbtn
				 // 
				 this->loginbtn->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->loginbtn->Location = System::Drawing::Point(245, 161);
				 this->loginbtn->Name = L"loginbtn";
				 this->loginbtn->Size = System::Drawing::Size(92, 23);
				 this->loginbtn->TabIndex = 3;
				 this->loginbtn->Text = L"Login";
				 this->loginbtn->UseVisualStyleBackColor = true;
				 this->loginbtn->Click += gcnew System::EventHandler(this, &LoginMenu::loginbtn_Click);
				 // 
				 // pwBox
				 // 
				 this->pwBox->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->pwBox->AsciiOnly = true;
				 this->pwBox->Location = System::Drawing::Point(159, 74);
				 this->pwBox->Name = L"pwBox";
				 this->pwBox->Size = System::Drawing::Size(178, 20);
				 this->pwBox->TabIndex = 1;
				 this->pwBox->UseSystemPasswordChar = true;
				 this->pwBox->Enter += gcnew System::EventHandler(this, &LoginMenu::pwBox_Enter);
				 this->pwBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &LoginMenu::pwBox_KeyPress);
				 // 
				 // LoginMenu
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(450, 212);
				 this->Controls->Add(this->pwBox);
				 this->Controls->Add(this->loginbtn);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->typeBox);
				 this->Controls->Add(this->idBox);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->label1);
				 this->MaximizeBox = false;
				 this->Name = L"LoginMenu";
				 this->Text = L"CEG Hypermarket ICMS";
				 this->Load += gcnew System::EventHandler(this, &LoginMenu::LoginMenu_Load);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	
		void LoginMenu_Load(System::Object^  sender, System::EventArgs^  e) ;
		void loginbtn_Click(System::Object^  sender, System::EventArgs^  e) ;		
		void idBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void pwBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void typeBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void idBox_Enter(System::Object^  sender, System::EventArgs^  e);	
		void pwBox_Enter(System::Object^  sender, System::EventArgs^  e);
	};
}
