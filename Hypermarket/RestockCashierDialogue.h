#pragma once
#include "inventory.h"
#include "wrapper.h"
namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Restock Cashier Dialogue
	/// Popup dialogue for cashier to restock product
	/// </summary>
	public ref class RestockCashierDialogue : public System::Windows::Forms::Form
	{
	private:	
		bool _saved;
		Inventory* _inv;
		Product* _product;
		System::ComponentModel::Container ^components;
		String ^PrdName, ^Barcode, ^Stock;
	private:
		System::Windows::Forms::TextBox^  barcodebox;
		System::Windows::Forms::Label^  barcodetxt;
		System::Windows::Forms::Label^  nametxt;
		System::Windows::Forms::TextBox^  namebox;
		System::Windows::Forms::GroupBox^  productgrp;
		System::Windows::Forms::TextBox^  stockbox;
		System::Windows::Forms::Label^  stocktxt;
		System::Windows::Forms::Button^  restockbtn;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->barcodebox = (gcnew System::Windows::Forms::TextBox());
			this->barcodetxt = (gcnew System::Windows::Forms::Label());
			this->nametxt = (gcnew System::Windows::Forms::Label());
			this->namebox = (gcnew System::Windows::Forms::TextBox());
			this->productgrp = (gcnew System::Windows::Forms::GroupBox());
			this->stockbox = (gcnew System::Windows::Forms::TextBox());
			this->stocktxt = (gcnew System::Windows::Forms::Label());
			this->restockbtn = (gcnew System::Windows::Forms::Button());
			this->productgrp->SuspendLayout();
			this->SuspendLayout();
			// 
			// barcodebox
			// 
			this->barcodebox->Location = System::Drawing::Point(97, 25);
			this->barcodebox->Name = L"barcodebox";
			this->barcodebox->ReadOnly = true;
			this->barcodebox->Size = System::Drawing::Size(200, 26);
			this->barcodebox->TabIndex = 20;
			// 
			// barcodetxt
			// 
			this->barcodetxt->AutoSize = true;
			this->barcodetxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->barcodetxt->Location = System::Drawing::Point(5, 26);
			this->barcodetxt->Name = L"barcodetxt";
			this->barcodetxt->Size = System::Drawing::Size(56, 17);
			this->barcodetxt->TabIndex = 22;
			this->barcodetxt->Text = L"Barcode";
			// 
			// nametxt
			// 
			this->nametxt->AutoSize = true;
			this->nametxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->nametxt->Location = System::Drawing::Point(5, 59);
			this->nametxt->Name = L"nametxt";
			this->nametxt->Size = System::Drawing::Size(43, 17);
			this->nametxt->TabIndex = 21;
			this->nametxt->Text = L"Name";
			// 
			// namebox
			// 
			this->namebox->Location = System::Drawing::Point(97, 57);
			this->namebox->Name = L"namebox";
			this->namebox->ReadOnly = true;
			this->namebox->Size = System::Drawing::Size(200, 26);
			this->namebox->TabIndex = 23;
			// 
			// productgrp
			// 
			this->productgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->productgrp->Controls->Add(this->stockbox);
			this->productgrp->Controls->Add(this->namebox);
			this->productgrp->Controls->Add(this->stocktxt);
			this->productgrp->Controls->Add(this->barcodebox);
			this->productgrp->Controls->Add(this->nametxt);
			this->productgrp->Controls->Add(this->barcodetxt);
			this->productgrp->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->productgrp->Location = System::Drawing::Point(12, 2);
			this->productgrp->Name = L"productgrp";
			this->productgrp->Size = System::Drawing::Size(307, 121);
			this->productgrp->TabIndex = 24;
			this->productgrp->TabStop = false;
			this->productgrp->Text = L"Product";
			// 
			// stockbox
			// 
			this->stockbox->Location = System::Drawing::Point(97, 87);
			this->stockbox->Name = L"stockbox";
			this->stockbox->Size = System::Drawing::Size(200, 26);
			this->stockbox->TabIndex = 27;
			this->stockbox->Text="";
			this->stockbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &RestockCashierDialogue::stockbox_KeyPress);
			// 
			// stocktxt
			// 
			this->stocktxt->AutoSize = true;
			this->stocktxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->stocktxt->Location = System::Drawing::Point(5, 91);
			this->stocktxt->Name = L"stocktxt";
			this->stocktxt->Size = System::Drawing::Size(86, 17);
			this->stocktxt->TabIndex = 28;
			this->stocktxt->Text = L"Current Stock";
			// 
			// restockbtn
			// 
			this->restockbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.5F));
			this->restockbtn->Location = System::Drawing::Point(328, 12);
			this->restockbtn->Name = L"restockbtn";
			this->restockbtn->Size = System::Drawing::Size(68, 108);
			this->restockbtn->TabIndex = 29;
			this->restockbtn->Text = L"Restock Product";
			this->restockbtn->UseVisualStyleBackColor = true;
			this->restockbtn->Click += gcnew System::EventHandler(this, &RestockCashierDialogue::restockbtn_Click);
			// 
			// RestockCashierDialogue
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 132);
			this->Controls->Add(this->restockbtn);
			this->Controls->Add(this->productgrp);
			this->Name = L"RestockCashierDialogue";
			this->Text = L"Restock Product";
			this->Load += gcnew System::EventHandler(this, &RestockCashierDialogue::RestockCashierDialogue_load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &RestockCashierDialogue:: CashierRestockDialogue_FormClosing);
			this->productgrp->ResumeLayout(false);
			this->productgrp->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		RestockCashierDialogue(Inventory* inv, Product* product);
	protected:
		~RestockCashierDialogue();
	private:
		void RestockCashierDialogue_load (System::Object^  sender, System::EventArgs^  e);
		void stockbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void restockbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void CashierRestockDialogue_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	};
}