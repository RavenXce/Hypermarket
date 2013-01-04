#include "stdafx.h"
#include "RestockCashierDialogue.h"

using namespace Hypermarket;

RestockCashierDialogue::RestockCashierDialogue(Inventory* inv, Product* product)
{
	_saved = true;
	_inv = inv;
	_product = product;
	PrdName = gcnew String(_product->getName().c_str());
	Barcode = gcnew String(_product->getBarcode().c_str());	
	StartPosition = FormStartPosition::CenterScreen;
	InitializeComponent();
}
RestockCashierDialogue::~RestockCashierDialogue()
{
	if (components)
	{
		delete components;
	}
}
void RestockCashierDialogue::RestockCashierDialogue_load (System::Object^  sender, System::EventArgs^  e) {
	barcodebox->Text = Barcode;
	namebox->Text = PrdName;
	stockbox->Select();
}
void RestockCashierDialogue::stockbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		restockbtn->PerformClick();
		e->Handled = true;
	}
	else _saved = false;
}
void RestockCashierDialogue::restockbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stockbox->Text=="") {
		MessageBox::Show(
			"Please input restock value", 
			"Error", MessageBoxButtons::OK,  MessageBoxIcon::Warning);
		return;
	}
	if(MessageBox::Show(
		"Change stock value?", 
		"Confirm", MessageBoxButtons::YesNo) ==  System::Windows::Forms::DialogResult::Yes) {
			_product->changeNumStock(Int32::Parse(stockbox->Text));
			_saved=true;
			_inv->productModified();
	}
	this->Close();
}
void RestockCashierDialogue::CashierRestockDialogue_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if(!_saved){
		System::Windows::Forms::DialogResult result = 
			MessageBox::Show(
			"Changes have not been saved. Close window without saving changes?", 
			"Warning", MessageBoxButtons::YesNoCancel,  MessageBoxIcon::Warning);
		if(result == System::Windows::Forms::DialogResult::No) restockbtn_Click(sender,e);
		else if(result == System::Windows::Forms::DialogResult::Cancel)  e->Cancel = true;
	}
}