#pragma once
#include "inventory.h"
#include "wrapper.h"

#define NPERISH 0
#define PERISH 1

namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ProductModUI
	/// Popup dialog to add or modify products
	/// </summary>
	public ref class ProductModUI : public System::Windows::Forms::Form
	{
	public:
		ProductModUI(Inventory* inv, Product* product, char type)
		{
			_type = type;
			_saved = true;
			_inv = inv;
			_product = product;
			if(product!=NULL){
				this->Name = "Modify Product";
				PrdName = gcnew String(_product->getName().c_str());
				Barcode = gcnew String(_product->getBarcode().c_str());
				Category = gcnew String(_product->getCategory().c_str());
				Manufacturer = gcnew String(_product->getManufacturer().c_str());
				Price = String::Format("{0:C}",_product->getPrice());
				Stock = gcnew String(_product->getNumStock().ToString());
				Sold = gcnew String(_product->getNumSold().ToString());
				if(product->isPerishable()){
					Discount = String::Format("{0:P}",_product->getDiscount()/100);			
					Expiry = gcnew String(Date(_product->getExpiry()).formatted().c_str());
				}
				else{
					Discount = "0.00 %";
					Expiry = "N/A";
				}	
			}
			else this->Name = "Add Product";
			StartPosition = FormStartPosition::CenterScreen;
			InitializeComponent();			
		}
	protected:
		~ProductModUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		bool _saved;
		char _type;
		Inventory* _inv;
		Product* _product;
		System::ComponentModel::Container ^components;
		String ^PrdName, ^Barcode, ^Category, ^Manufacturer, ^Price, ^Stock, ^Sold, ^Expiry, ^Discount;


#pragma region Windows Form Automated Declaration Region
		System::Windows::Forms::GroupBox^  productgrp;
		System::Windows::Forms::TextBox^  stockbox;
		System::Windows::Forms::Label^  stocktxt;
		System::Windows::Forms::TextBox^  soldbox;
		System::Windows::Forms::Label^  soldtxt;
		System::Windows::Forms::Label^  expirytxt;
		System::Windows::Forms::Label^  discounttxt;
		System::Windows::Forms::Label^  pricetxt;
		System::Windows::Forms::TextBox^  categorybox;
		System::Windows::Forms::MaskedTextBox^  pricebox;
		System::Windows::Forms::MaskedTextBox^  discountbox;
		System::Windows::Forms::Label^  categorytxt;
		System::Windows::Forms::TextBox^  manubox;
		System::Windows::Forms::Label^  manufacturertxt;
		System::Windows::Forms::TextBox^  barcodebox;
		System::Windows::Forms::Label^  barcodetxt;
		System::Windows::Forms::TextBox^  namebox;
		System::Windows::Forms::Label^  nametxt;
		System::Windows::Forms::Button^  savebtn;
		System::Windows::Forms::DateTimePicker^  expirybox_picker;
		System::Windows::Forms::MaskedTextBox^  expirybox;
		System::Windows::Forms::Button^  resetbtn;
#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->productgrp = (gcnew System::Windows::Forms::GroupBox());
			this->expirybox_picker = (gcnew System::Windows::Forms::DateTimePicker());
			this->pricebox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->discountbox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->stockbox = (gcnew System::Windows::Forms::TextBox());
			this->stocktxt = (gcnew System::Windows::Forms::Label());
			this->soldbox = (gcnew System::Windows::Forms::TextBox());
			this->soldtxt = (gcnew System::Windows::Forms::Label());
			this->expirytxt = (gcnew System::Windows::Forms::Label());
			this->discounttxt = (gcnew System::Windows::Forms::Label());
			this->pricetxt = (gcnew System::Windows::Forms::Label());
			this->categorybox = (gcnew System::Windows::Forms::TextBox());
			this->categorytxt = (gcnew System::Windows::Forms::Label());
			this->manubox = (gcnew System::Windows::Forms::TextBox());
			this->manufacturertxt = (gcnew System::Windows::Forms::Label());
			this->barcodebox = (gcnew System::Windows::Forms::TextBox());
			this->barcodetxt = (gcnew System::Windows::Forms::Label());
			this->namebox = (gcnew System::Windows::Forms::TextBox());
			this->nametxt = (gcnew System::Windows::Forms::Label());
			this->expirybox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->savebtn = (gcnew System::Windows::Forms::Button());
			this->resetbtn = (gcnew System::Windows::Forms::Button());
			this->productgrp->SuspendLayout();
			this->SuspendLayout();
			// 
			// productgrp
			// 
			this->productgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->productgrp->Controls->Add(this->expirybox_picker);
			this->productgrp->Controls->Add(this->pricebox);
			this->productgrp->Controls->Add(this->discountbox);
			this->productgrp->Controls->Add(this->stockbox);
			this->productgrp->Controls->Add(this->stocktxt);
			this->productgrp->Controls->Add(this->soldbox);
			this->productgrp->Controls->Add(this->soldtxt);
			this->productgrp->Controls->Add(this->expirytxt);
			this->productgrp->Controls->Add(this->discounttxt);
			this->productgrp->Controls->Add(this->pricetxt);
			this->productgrp->Controls->Add(this->categorybox);
			this->productgrp->Controls->Add(this->categorytxt);
			this->productgrp->Controls->Add(this->manubox);
			this->productgrp->Controls->Add(this->manufacturertxt);
			this->productgrp->Controls->Add(this->barcodebox);
			this->productgrp->Controls->Add(this->barcodetxt);
			this->productgrp->Controls->Add(this->namebox);
			this->productgrp->Controls->Add(this->nametxt);
			this->productgrp->Controls->Add(this->expirybox);
			this->productgrp->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->productgrp->Location = System::Drawing::Point(12, 2);
			this->productgrp->Name = L"productgrp";
			this->productgrp->Size = System::Drawing::Size(351, 280);
			this->productgrp->TabIndex = 0;
			this->productgrp->TabStop = false;
			this->productgrp->Text = L"Product";
			// 
			// expirybox_picker
			// 
			this->expirybox_picker->CustomFormat = L"dd/MM/yyyy";
			this->expirybox_picker->Enabled = false;
			this->expirybox_picker->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->expirybox_picker->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->expirybox_picker->Location = System::Drawing::Point(125, 190);
			this->expirybox_picker->Name = L"expirybox_picker";
			this->expirybox_picker->Size = System::Drawing::Size(208, 26);
			this->expirybox_picker->TabIndex = 6;
			this->expirybox_picker->Visible = false;
			// 
			// pricebox
			// 
			this->pricebox->Location = System::Drawing::Point(125, 133);
			this->pricebox->Name = L"pricebox";
			this->pricebox->Size = System::Drawing::Size(208, 26);
			this->pricebox->TabIndex = 4;
			this->pricebox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::numField_KeyPress);
			// 
			// discountbox
			// 
			this->discountbox->Location = System::Drawing::Point(125, 161);
			this->discountbox->Name = L"discountbox";
			this->discountbox->Size = System::Drawing::Size(208, 26);
			this->discountbox->TabIndex = 5;
			this->discountbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::numField_KeyPress);
			// 
			// stockbox
			// 
			this->stockbox->Location = System::Drawing::Point(125, 247);
			this->stockbox->Name = L"stockbox";
			this->stockbox->Size = System::Drawing::Size(208, 26);
			this->stockbox->TabIndex = 8;
			this->stockbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::numField_KeyPress);
			// 
			// stocktxt
			// 
			this->stocktxt->AutoSize = true;
			this->stocktxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->stocktxt->Location = System::Drawing::Point(9, 251);
			this->stocktxt->Name = L"stocktxt";
			this->stocktxt->Size = System::Drawing::Size(86, 17);
			this->stocktxt->TabIndex = 26;
			this->stocktxt->Text = L"Current Stock";
			// 
			// soldbox
			// 
			this->soldbox->Location = System::Drawing::Point(125, 218);
			this->soldbox->Name = L"soldbox";
			this->soldbox->Size = System::Drawing::Size(208, 26);
			this->soldbox->TabIndex = 7;
			this->soldbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::numField_KeyPress);
			// 
			// soldtxt
			// 
			this->soldtxt->AutoSize = true;
			this->soldtxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->soldtxt->Location = System::Drawing::Point(9, 222);
			this->soldtxt->Name = L"soldtxt";
			this->soldtxt->Size = System::Drawing::Size(67, 17);
			this->soldtxt->TabIndex = 25;
			this->soldtxt->Text = L"Units Sold";
			// 
			// expirytxt
			// 
			this->expirytxt->AutoSize = true;
			this->expirytxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->expirytxt->Location = System::Drawing::Point(9, 193);
			this->expirytxt->Name = L"expirytxt";
			this->expirytxt->Size = System::Drawing::Size(43, 17);
			this->expirytxt->TabIndex = 24;
			this->expirytxt->Text = L"Expiry";
			// 
			// discounttxt
			// 
			this->discounttxt->AutoSize = true;
			this->discounttxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->discounttxt->Location = System::Drawing::Point(9, 165);
			this->discounttxt->Name = L"discounttxt";
			this->discounttxt->Size = System::Drawing::Size(58, 17);
			this->discounttxt->TabIndex = 23;
			this->discounttxt->Text = L"Discount";
			// 
			// pricetxt
			// 
			this->pricetxt->AutoSize = true;
			this->pricetxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->pricetxt->Location = System::Drawing::Point(9, 137);
			this->pricetxt->Name = L"pricetxt";
			this->pricetxt->Size = System::Drawing::Size(36, 17);
			this->pricetxt->TabIndex = 22;
			this->pricetxt->Text = L"Price";
			// 
			// categorybox
			// 
			this->categorybox->Location = System::Drawing::Point(125, 77);
			this->categorybox->Name = L"categorybox";
			this->categorybox->Size = System::Drawing::Size(208, 26);
			this->categorybox->TabIndex = 2;
			this->categorybox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::field_KeyPress);
			// 
			// categorytxt
			// 
			this->categorytxt->AutoSize = true;
			this->categorytxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->categorytxt->Location = System::Drawing::Point(9, 81);
			this->categorytxt->Name = L"categorytxt";
			this->categorytxt->Size = System::Drawing::Size(61, 17);
			this->categorytxt->TabIndex = 20;
			this->categorytxt->Text = L"Category";
			// 
			// manubox
			// 
			this->manubox->Location = System::Drawing::Point(125, 105);
			this->manubox->Name = L"manubox";
			this->manubox->Size = System::Drawing::Size(208, 26);
			this->manubox->TabIndex = 3;
			this->manubox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::field_KeyPress);
			// 
			// manufacturertxt
			// 
			this->manufacturertxt->AutoSize = true;
			this->manufacturertxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->manufacturertxt->Location = System::Drawing::Point(9, 109);
			this->manufacturertxt->Name = L"manufacturertxt";
			this->manufacturertxt->Size = System::Drawing::Size(86, 17);
			this->manufacturertxt->TabIndex = 21;
			this->manufacturertxt->Text = L"Manufacturer";
			// 
			// barcodebox
			// 
			this->barcodebox->Location = System::Drawing::Point(125, 20);
			this->barcodebox->Name = L"barcodebox";
			this->barcodebox->ReadOnly = true;
			this->barcodebox->Size = System::Drawing::Size(208, 26);
			this->barcodebox->TabIndex = 0;
			this->barcodebox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::numField_KeyPress);
			// 
			// barcodetxt
			// 
			this->barcodetxt->AutoSize = true;
			this->barcodetxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->barcodetxt->Location = System::Drawing::Point(9, 24);
			this->barcodetxt->Name = L"barcodetxt";
			this->barcodetxt->Size = System::Drawing::Size(56, 17);
			this->barcodetxt->TabIndex = 19;
			this->barcodetxt->Text = L"Barcode";
			// 
			// namebox
			// 
			this->namebox->Location = System::Drawing::Point(125, 49);
			this->namebox->Name = L"namebox";
			this->namebox->Size = System::Drawing::Size(208, 26);
			this->namebox->TabIndex = 1;
			this->namebox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ProductModUI::field_KeyPress);
			// 
			// nametxt
			// 
			this->nametxt->AutoSize = true;
			this->nametxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nametxt->Location = System::Drawing::Point(9, 53);
			this->nametxt->Name = L"nametxt";
			this->nametxt->Size = System::Drawing::Size(43, 17);
			this->nametxt->TabIndex = 18;
			this->nametxt->Text = L"Name";
			// 
			// expirybox
			// 
			this->expirybox->Enabled = false;
			this->expirybox->Location = System::Drawing::Point(125, 190);
			this->expirybox->Name = L"expirybox";
			this->expirybox->ReadOnly = true;
			this->expirybox->Size = System::Drawing::Size(208, 26);
			this->expirybox->TabIndex = 6;
			// 
			// savebtn
			// 
			this->savebtn->Location = System::Drawing::Point(369, 231);
			this->savebtn->Name = L"savebtn";
			this->savebtn->Size = System::Drawing::Size(100, 49);
			this->savebtn->TabIndex = 9;
			this->savebtn->Text = L"Save Changes";
			this->savebtn->UseVisualStyleBackColor = true;
			this->savebtn->Click += gcnew System::EventHandler(this, &ProductModUI::savebtn_Click);
			// 
			// resetbtn
			// 
			this->resetbtn->Location = System::Drawing::Point(369, 176);
			this->resetbtn->Name = L"resetbtn";
			this->resetbtn->Size = System::Drawing::Size(100, 49);
			this->resetbtn->TabIndex = 10;
			this->resetbtn->Text = L"Reset Changes";
			this->resetbtn->UseVisualStyleBackColor = true;
			this->resetbtn->Click += gcnew System::EventHandler(this, &ProductModUI::resetbtn_Click);
			// 
			// ProductModUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(479, 292);
			this->Controls->Add(this->resetbtn);
			this->Controls->Add(this->savebtn);
			this->Controls->Add(this->productgrp);
			this->Name = L"ProductModUI";
			this->Text = L"Modify Product";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ProductModUI::ProductModUI_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ProductModUI::ProductModUI_Load);
			this->productgrp->ResumeLayout(false);
			this->productgrp->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		void ProductModUI_Load(System::Object^  sender, System::EventArgs^  e);
		void ProductModUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		void textEntered();
		void numField_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void field_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void resetFields();
		void resetbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void savebtn_Click(System::Object^  sender, System::EventArgs^  e);
		bool save();		
	};
}
