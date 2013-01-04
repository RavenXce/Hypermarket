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
	/// Summary for Sell Cashier Dialogue
	/// Popup dialogue for cashier to sell product
	/// </summary>
	public ref class SellCashierDialogue : public System::Windows::Forms::Form
	{
	private:
		bool _saved;
		Inventory* _inv;
		Product* _product;
		System::ComponentModel::Container ^components;
		String ^PrdName, ^Barcode, ^Sale;
	private:
		System::Windows::Forms::TextBox^  barcodebox;
		System::Windows::Forms::Label^  barcodetxt;
		System::Windows::Forms::Label^  nametxt;
		System::Windows::Forms::TextBox^  namebox;
		System::Windows::Forms::GroupBox^  productgrp;
		System::Windows::Forms::TextBox^  salebox;
		System::Windows::Forms::Label^  saletxt;
		System::Windows::Forms::Button^  sellbtn;

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
			this->salebox = (gcnew System::Windows::Forms::TextBox());
			this->saletxt = (gcnew System::Windows::Forms::Label());
			this->sellbtn = (gcnew System::Windows::Forms::Button());
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
			this->productgrp->Controls->Add(this->salebox);
			this->productgrp->Controls->Add(this->namebox);
			this->productgrp->Controls->Add(this->saletxt);
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
			// salebox
			// 
			this->salebox->Location = System::Drawing::Point(97, 87);
			this->salebox->Name = L"salebox";
			this->salebox->Size = System::Drawing::Size(200, 26);
			this->salebox->TabIndex = 27;
			this->salebox->Text="";
			this->salebox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SellCashierDialogue::sellbox_KeyPress);
			// 
			// saletxt
			// 
			this->saletxt->AutoSize = true;
			this->saletxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->saletxt->Location = System::Drawing::Point(5, 91);
			this->saletxt->Name = L"saletxt";
			this->saletxt->Size = System::Drawing::Size(86, 17);
			this->saletxt->TabIndex = 28;
			this->saletxt->Text = L"Sell";
			// 
			// sellbtn
			// 
			this->sellbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.5F));
			this->sellbtn->Location = System::Drawing::Point(328, 12);
			this->sellbtn->Name = L"sellbtn";
			this->sellbtn->Size = System::Drawing::Size(68, 108);
			this->sellbtn->TabIndex = 29;
			this->sellbtn->Text = L"Sell Product";
			this->sellbtn->UseVisualStyleBackColor = true;
			this->sellbtn->Click += gcnew System::EventHandler(this, &SellCashierDialogue::sellbtn_Click);
			// 
			// SellCashierDialogue
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 132);
			this->Controls->Add(this->sellbtn);
			this->Controls->Add(this->productgrp);
			this->Name = L"SellCashierDialogue";
			this->Text = L"Sell Product";
			this->Load += gcnew System::EventHandler(this, &SellCashierDialogue::SellCashierDialogue_load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SellCashierDialogue:: SellCashierDialogue_FormClosing);
			this->productgrp->ResumeLayout(false);
			this->productgrp->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	public:
		SellCashierDialogue(Inventory* inv, Product* product);
	protected:
		~SellCashierDialogue();
	private:
		void SellCashierDialogue_load (System::Object^  sender, System::EventArgs^  e);
		void sellbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void sellbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void SellCashierDialogue_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	};
}