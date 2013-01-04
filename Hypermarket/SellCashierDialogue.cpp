#include "stdafx.h"
#include "SellCashierDialogue.h"

using namespace Hypermarket;

SellCashierDialogue::SellCashierDialogue(Inventory* inv, Product* product)
{
	_saved = true;
	_inv = inv;
	_product = product;
	PrdName = gcnew String(_product->getName().c_str());
	Barcode = gcnew String(_product->getBarcode().c_str());			
	StartPosition = FormStartPosition::CenterScreen;
	InitializeComponent();
}

SellCashierDialogue::~SellCashierDialogue()
{
	if (components)
	{
		delete components;
	}
}

void SellCashierDialogue::SellCashierDialogue_load (System::Object^  sender, System::EventArgs^  e) {
	barcodebox->Text = Barcode;
	namebox->Text = PrdName;
	salebox->Select();
}
void SellCashierDialogue::sellbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		sellbtn->PerformClick();
		e->Handled = true;
	}
	else _saved = false;
}
void SellCashierDialogue::sellbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if (salebox->Text=="") {
		MessageBox::Show(
			"Please input number to be sold", 
			"Error", MessageBoxButtons::OK,  MessageBoxIcon::Warning);
		return;
	}
	if(MessageBox::Show(
		"Sell product?", 
		"Confirm", MessageBoxButtons::YesNo) ==  System::Windows::Forms::DialogResult::Yes) {
			if(Int32::Parse(salebox->Text)>_product->getNumStock()) {
				MessageBox::Show(
					"Insufficient inventory stock!", 
					"Error", MessageBoxButtons::OK,  MessageBoxIcon::Warning);
				return;
			}
			_product->sell(Int32::Parse(salebox->Text));
			_saved=true;
			_inv->productModified();
	}
	this->Close();
}
void SellCashierDialogue::SellCashierDialogue_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if(!_saved){
		System::Windows::Forms::DialogResult result = 
			MessageBox::Show(
			"Changes have not been saved. Close window without saving changes?", 
			"Warning", MessageBoxButtons::YesNoCancel,  MessageBoxIcon::Warning);
		if(result == System::Windows::Forms::DialogResult::No) sellbtn_Click(sender,e);
		else if(result == System::Windows::Forms::DialogResult::Cancel)  e->Cancel = true;
	}
}