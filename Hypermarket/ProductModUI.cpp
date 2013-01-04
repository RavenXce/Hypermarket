#include "stdafx.h"
#include "ProductModUI.h"

using namespace Hypermarket;

void ProductModUI::ProductModUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if(!_saved){
		System::Windows::Forms::DialogResult result = 
			MessageBox::Show(
			"Changes have not been saved. Save changes before exiting?", 
			"Warning", MessageBoxButtons::YesNoCancel,  MessageBoxIcon::Warning);
		if(result == System::Windows::Forms::DialogResult::Yes) savebtn_Click(sender,e);					 
		else if(result == System::Windows::Forms::DialogResult::Cancel)  e->Cancel = true;
	}
}
void ProductModUI::ProductModUI_Load(System::Object^  sender, System::EventArgs^  e) {
	resetFields();
}
void ProductModUI::textEntered(){
	_saved = false;
}
void ProductModUI::numField_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		if(!(safe_cast<TextBoxBase^>(sender) == pricebox && (e->KeyChar == '$'  || e->KeyChar == '.')))
			if(!(safe_cast<TextBoxBase^>(sender) == discountbox && (e->KeyChar == '%' || e->KeyChar == '.')))
				if(!(safe_cast<TextBoxBase^>(sender) == expirybox && (e->KeyChar == '/' )))
					e->Handled = true;
	field_KeyPress(sender,e);
}
void ProductModUI::field_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		savebtn->PerformClick();
		e->Handled = true;
	}
	else _saved = false;
}
void ProductModUI::resetFields(){
	if(_product!=NULL){
		namebox->Text = PrdName;
		barcodebox->Text = Barcode;
		categorybox->Text = Category;
		manubox->Text = Manufacturer;
		pricebox->Text = Price;
		stockbox->Text = Stock;					 
		soldbox->Text = Sold;	
		soldbox->ReadOnly = true;
		expirybox->Enabled = true;
		expirybox->Visible = true;
		expirybox_picker->Enabled = false;
		expirybox_picker->Visible = false;
		expirybox->Text = Expiry;			 
		discountbox->Text = Discount;
		if(_product->isPerishable()) discountbox->ReadOnly = false;
		else discountbox->ReadOnly = true;
	}
	else{
		if(_type == NPERISH){
			expirybox->Enabled = true;
			expirybox->Visible = true;
			expirybox_picker->Enabled = false;
			expirybox_picker->Visible = false;
			expirybox->Text = Expiry;								 
			discountbox->ReadOnly = true;						
		}
		else {						 
			expirybox->Enabled = false;
			expirybox->Visible = false;
			expirybox_picker->Enabled = true;
			expirybox_picker->Visible = true;
			expirybox->Text = Expiry;		
			discountbox->ReadOnly = false;	
		}
		barcodebox->ReadOnly = false;
		barcodebox->Focus();
		barcodebox->Select();
	}
}
void ProductModUI::resetbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(MessageBox::Show(
		"Reset changes?", 
		"Confirm", MessageBoxButtons::YesNo) ==  System::Windows::Forms::DialogResult::Yes)
		resetFields();
}
void ProductModUI::savebtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(MessageBox::Show(
		"Save product changes?", 
		"Confirm", MessageBoxButtons::YesNo) ==  System::Windows::Forms::DialogResult::Yes){
			if(save()){
				_saved = true;				// change saved to memory
				_inv->productModified();	// not saved to file
				this->Close();
			}
	}
}
bool ProductModUI::save(){
	/* Empty fields check */
	if(namebox->Text == "" || categorybox->Text == "" || manubox->Text == "" || pricebox->Text == "" ||
		soldbox->Text == "" || stockbox->Text == "" || discountbox->Text == ""){
			MessageBox::Show(
				"Cannot have empty fields!", 
				"Error", MessageBoxButtons::OK,  MessageBoxIcon::Error);
			return false;
	}
	/* Else process fields */
	else{
		double chkPrice;
		double chkDiscount;
		try{
			chkPrice = Double::Parse(pricebox->Text,Globalization::NumberStyles::Currency);				 						 
		}
		catch(FormatException^ e)
		{
			MessageBox::Show(
				"Entered price has an invalid format!", 
				"Error", MessageBoxButtons::OK,  MessageBoxIcon::Error);
			return false;
		}
		if(_type == PERISH){
			try{
				if(discountbox->Text->Contains("%"))
					chkDiscount = Double::Parse(discountbox->Text->Substring(0, discountbox->Text->IndexOf('%')));
				else chkDiscount = Double::Parse(discountbox->Text);
				if(chkDiscount < 0 || chkDiscount > 100){
					MessageBox::Show(
						"Invalid discount range! Please enter a valid range between 0% and 100%.", 
						"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return false;
				}
			}
			catch(FormatException^ e)
			{
				MessageBox::Show(
					"Entered discount has an invalid format!", 
					"Error", MessageBoxButtons::OK,  MessageBoxIcon::Error);
				return false;
			}
		}
		/* Modify product */
		if(_product!=NULL){
			if(namebox->Text != PrdName)
				_product->changeName(Wrapper::toUnmanagedString(namebox->Text));
			if(categorybox->Text != Category)
				_product->changeCategory(Wrapper::toUnmanagedString(categorybox->Text));
			if(manubox->Text != Manufacturer)
				_product->changeManufacturer(Wrapper::toUnmanagedString(manubox->Text));
			if(pricebox->Text != Price)
				_product->changePrice(chkPrice);
			if(stockbox->Text != Stock)
				_product->changeNumStock(Int32::Parse(stockbox->Text));
			if(_product->isPerishable())
				if(discountbox->Text != Discount)
					_product->changeDiscount(chkDiscount);
		}
		/* Add new product */
		else{
			if(_type==NPERISH){
				if(!_inv->addProduct(Product(
					Wrapper::toUnmanagedString(namebox->Text),
					Wrapper::toUnmanagedString(categorybox->Text),
					Wrapper::toUnmanagedString(barcodebox->Text),
					Wrapper::toUnmanagedString(manubox->Text),
					chkPrice,
					Int32::Parse(stockbox->Text),
					Int32::Parse(soldbox->Text)))){
						MessageBox::Show(
							"There already exists a product with the same barcode!", 
							"Error", MessageBoxButtons::OK,  MessageBoxIcon::Error);
						return false;
				}
			}
			else{							 
				String^ inputDate =  expirybox_picker->Value.Day.ToString("00") +
					expirybox_picker->Value.Month.ToString("00") +
					expirybox_picker->Value.Year.ToString("0000");
				if(!_inv->addProduct(PerishableProduct(
					Wrapper::toUnmanagedString(namebox->Text),
					Wrapper::toUnmanagedString(categorybox->Text),
					Wrapper::toUnmanagedString(barcodebox->Text),
					Wrapper::toUnmanagedString(manubox->Text),
					chkPrice,
					Int32::Parse(stockbox->Text),
					Int32::Parse(soldbox->Text),
					Int32::Parse(inputDate),
					chkDiscount))){
						MessageBox::Show(
							"There already exists a product with the same barcode!", 
							"Error", MessageBoxButtons::OK,  MessageBoxIcon::Error);
						return false;
				}
			}
		}
	}
	return true;
}


