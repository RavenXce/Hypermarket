#pragma once
#include "MainUI.h"
#include "ListViewItemComparer.h"
#include "RestockCashierDialogue.h"
#include "SellCashierDialogue.h"
#include "date.h"

namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CashierUI
	/// UI Form for Cashier Mode
	/// </summary>
	public ref class CashierUI : public MainUI
	{
	public:
		CashierUI(int* next, string* curUser, Inventory* inv, Password* pwDB) : MainUI(next,curUser,inv,pwDB) {
			displayList = new vector<Product*>;
			InitializeComponent();
		}
	protected:
		~CashierUI()
		{
			delete displayList;
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container ^components;		
		vector<Product*>* displayList;

#pragma region Windows Form Automated Declaration Region		
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerFillResults; 
	private: System::Windows::Forms::GroupBox^  productgrp;
	private: System::Windows::Forms::TextBox^  namebox;
	private: System::Windows::Forms::TextBox^  barcodebox;
	private: System::Windows::Forms::TextBox^  categorybox;
	private: System::Windows::Forms::TextBox^  manubox;
	private: System::Windows::Forms::TextBox^  pricebox;
	private: System::Windows::Forms::TextBox^  stockbox;
	private: System::Windows::Forms::TextBox^  soldbox;
	private: System::Windows::Forms::TextBox^  expirybox;
	private: System::Windows::Forms::TextBox^  discountbox;	
	private: System::Windows::Forms::Label^  nametxt;
	private: System::Windows::Forms::Label^  categorytxt;
	private: System::Windows::Forms::Label^  manufacturertxt;
	private: System::Windows::Forms::Label^  barcodetxt;
	private: System::Windows::Forms::Label^  pricetxt;
	private: System::Windows::Forms::Label^  expirytxt;
	private: System::Windows::Forms::Label^  discounttxt;
	private: System::Windows::Forms::Label^  stocktxt;
	private: System::Windows::Forms::Label^  soldtxt;	
	private: System::Windows::Forms::GroupBox^  searchgroup;
	private: System::Windows::Forms::Label^  searchtxt;
	private: System::Windows::Forms::TextBox^  searchBox;
	private: System::Windows::Forms::CheckedListBox^  searchType;
	private: System::Windows::Forms::Button^  restockbtn;
	private: System::Windows::Forms::Button^  gobtn;
	private: System::Windows::Forms::ListView^  resultsListView;
	private: System::Windows::Forms::GroupBox^  resultgrp;
	private: System::Windows::Forms::ColumnHeader^  nameCol;
	private: System::Windows::Forms::ColumnHeader^  categoryCol;
	private: System::Windows::Forms::ColumnHeader^  manufacturerCol;
	private: System::Windows::Forms::ColumnHeader^  barcodeCol;
	private: System::Windows::Forms::Button^  sellbtn;

#pragma endregion
#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CashierUI::typeid));
				 this->backgroundWorkerFillResults = (gcnew System::ComponentModel::BackgroundWorker());
				 this->productgrp = (gcnew System::Windows::Forms::GroupBox());
				 this->stockbox = (gcnew System::Windows::Forms::TextBox());
				 this->stocktxt = (gcnew System::Windows::Forms::Label());
				 this->soldbox = (gcnew System::Windows::Forms::TextBox());
				 this->soldtxt = (gcnew System::Windows::Forms::Label());
				 this->expirybox = (gcnew System::Windows::Forms::TextBox());
				 this->expirytxt = (gcnew System::Windows::Forms::Label());
				 this->discountbox = (gcnew System::Windows::Forms::TextBox());
				 this->discounttxt = (gcnew System::Windows::Forms::Label());
				 this->pricebox = (gcnew System::Windows::Forms::TextBox());
				 this->pricetxt = (gcnew System::Windows::Forms::Label());
				 this->categorybox = (gcnew System::Windows::Forms::TextBox());
				 this->categorytxt = (gcnew System::Windows::Forms::Label());
				 this->manubox = (gcnew System::Windows::Forms::TextBox());
				 this->manufacturertxt = (gcnew System::Windows::Forms::Label());
				 this->barcodebox = (gcnew System::Windows::Forms::TextBox());
				 this->barcodetxt = (gcnew System::Windows::Forms::Label());
				 this->namebox = (gcnew System::Windows::Forms::TextBox());
				 this->nametxt = (gcnew System::Windows::Forms::Label());
				 this->restockbtn = (gcnew System::Windows::Forms::Button());
				 this->sellbtn = (gcnew System::Windows::Forms::Button());
				 this->searchBox = (gcnew System::Windows::Forms::TextBox());
				 this->searchType = (gcnew System::Windows::Forms::CheckedListBox());
				 this->searchgroup = (gcnew System::Windows::Forms::GroupBox());
				 this->gobtn = (gcnew System::Windows::Forms::Button());
				 this->searchtxt = (gcnew System::Windows::Forms::Label());
				 this->resultsListView = (gcnew System::Windows::Forms::ListView());
				 this->nameCol = (gcnew System::Windows::Forms::ColumnHeader());
				 this->categoryCol = (gcnew System::Windows::Forms::ColumnHeader());
				 this->manufacturerCol = (gcnew System::Windows::Forms::ColumnHeader());
				 this->barcodeCol = (gcnew System::Windows::Forms::ColumnHeader());
				 this->resultgrp = (gcnew System::Windows::Forms::GroupBox());
				 this->productgrp->SuspendLayout();
				 this->searchgroup->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // backgroundWorkerFillResults
				 // 
				 this->backgroundWorkerFillResults->WorkerReportsProgress = true;
				 this->backgroundWorkerFillResults->WorkerSupportsCancellation = true;
				 this->backgroundWorkerFillResults->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &CashierUI::backgroundWorkerFillResults_DoWork);
				 this->backgroundWorkerFillResults->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &CashierUI::backgroundWorkerFillResults_RunWorkerCompleted);
				 // 
				 // productgrp
				 // 
				 this->productgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->productgrp->Controls->Add(this->stockbox);
				 this->productgrp->Controls->Add(this->stocktxt);
				 this->productgrp->Controls->Add(this->soldbox);
				 this->productgrp->Controls->Add(this->soldtxt);
				 this->productgrp->Controls->Add(this->expirybox);
				 this->productgrp->Controls->Add(this->expirytxt);
				 this->productgrp->Controls->Add(this->discountbox);
				 this->productgrp->Controls->Add(this->discounttxt);
				 this->productgrp->Controls->Add(this->pricebox);
				 this->productgrp->Controls->Add(this->pricetxt);
				 this->productgrp->Controls->Add(this->categorybox);
				 this->productgrp->Controls->Add(this->categorytxt);
				 this->productgrp->Controls->Add(this->manubox);
				 this->productgrp->Controls->Add(this->manufacturertxt);
				 this->productgrp->Controls->Add(this->barcodebox);
				 this->productgrp->Controls->Add(this->barcodetxt);
				 this->productgrp->Controls->Add(this->namebox);
				 this->productgrp->Controls->Add(this->nametxt);
				 this->productgrp->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->productgrp->Location = System::Drawing::Point(0, 137);
				 this->productgrp->Name = L"productgrp";
				 this->productgrp->Size = System::Drawing::Size(351, 280);
				 this->productgrp->TabIndex = 15;
				 this->productgrp->TabStop = false;
				 this->productgrp->Text = L"Product";
				 // 
				 // stockbox
				 // 
				 this->stockbox->Location = System::Drawing::Point(125, 247);
				 this->stockbox->Name = L"stockbox";
				 this->stockbox->ReadOnly = true;
				 this->stockbox->Size = System::Drawing::Size(208, 26);
				 this->stockbox->TabIndex = 13;
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
				 this->soldbox->ReadOnly = true;
				 this->soldbox->Size = System::Drawing::Size(208, 26);
				 this->soldbox->TabIndex = 12;
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
				 // expirybox
				 // 
				 this->expirybox->Location = System::Drawing::Point(125, 189);
				 this->expirybox->Name = L"expirybox";
				 this->expirybox->ReadOnly = true;
				 this->expirybox->Size = System::Drawing::Size(208, 26);
				 this->expirybox->TabIndex = 11;
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
				 // discountbox
				 // 
				 this->discountbox->Location = System::Drawing::Point(125, 161);
				 this->discountbox->Name = L"discountbox";
				 this->discountbox->ReadOnly = true;
				 this->discountbox->Size = System::Drawing::Size(208, 26);
				 this->discountbox->TabIndex = 10;
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
				 // pricebox
				 // 
				 this->pricebox->Location = System::Drawing::Point(125, 133);
				 this->pricebox->Name = L"pricebox";
				 this->pricebox->ReadOnly = true;
				 this->pricebox->Size = System::Drawing::Size(208, 26);
				 this->pricebox->TabIndex = 9;
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
				 this->categorybox->Location = System::Drawing::Point(125, 78);
				 this->categorybox->Name = L"categorybox";
				 this->categorybox->ReadOnly = true;
				 this->categorybox->Size = System::Drawing::Size(208, 26);
				 this->categorybox->TabIndex = 7;
				 // 
				 // categorytxt
				 // 
				 this->categorytxt->AutoSize = true;
				 this->categorytxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->categorytxt->Location = System::Drawing::Point(9, 82);
				 this->categorytxt->Name = L"categorytxt";
				 this->categorytxt->Size = System::Drawing::Size(61, 17);
				 this->categorytxt->TabIndex = 20;
				 this->categorytxt->Text = L"Category";
				 // 
				 // manubox
				 // 
				 this->manubox->Location = System::Drawing::Point(125, 105);
				 this->manubox->Name = L"manubox";
				 this->manubox->ReadOnly = true;
				 this->manubox->Size = System::Drawing::Size(208, 26);
				 this->manubox->TabIndex = 8;
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
				 this->barcodebox->Location = System::Drawing::Point(125, 50);
				 this->barcodebox->Name = L"barcodebox";
				 this->barcodebox->ReadOnly = true;
				 this->barcodebox->Size = System::Drawing::Size(208, 26);
				 this->barcodebox->TabIndex = 6;
				 // 
				 // barcodetxt
				 // 
				 this->barcodetxt->AutoSize = true;
				 this->barcodetxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->barcodetxt->Location = System::Drawing::Point(9, 54);
				 this->barcodetxt->Name = L"barcodetxt";
				 this->barcodetxt->Size = System::Drawing::Size(56, 17);
				 this->barcodetxt->TabIndex = 19;
				 this->barcodetxt->Text = L"Barcode";
				 // 
				 // namebox
				 // 
				 this->namebox->Location = System::Drawing::Point(125, 22);
				 this->namebox->Name = L"namebox";
				 this->namebox->ReadOnly = true;
				 this->namebox->Size = System::Drawing::Size(208, 26);
				 this->namebox->TabIndex = 5;
				 // 
				 // nametxt
				 // 
				 this->nametxt->AutoSize = true;
				 this->nametxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->nametxt->Location = System::Drawing::Point(9, 26);
				 this->nametxt->Name = L"nametxt";
				 this->nametxt->Size = System::Drawing::Size(43, 17);
				 this->nametxt->TabIndex = 18;
				 this->nametxt->Text = L"Name";
				 // 
				 // restockbtn
				 // 
				 this->restockbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
				 this->restockbtn->Location = System::Drawing::Point(371, 59);
				 this->restockbtn->Name = L"restockbtn";
				 this->restockbtn->Size = System::Drawing::Size(102, 39);
				 this->restockbtn->TabIndex = 4;
				 this->restockbtn->Text = L"Restock";
				 this->restockbtn->UseVisualStyleBackColor = true;
				 this->restockbtn->Click += gcnew System::EventHandler(this, &CashierUI::restockbtn_Click);
				 // 
				 // sellbtn
				 // 
				 this->sellbtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
				 this->sellbtn->Location = System::Drawing::Point(371, 16);
				 this->sellbtn->Name = L"sellbtn";
				 this->sellbtn->Size = System::Drawing::Size(102, 39);
				 this->sellbtn->TabIndex = 3;
				 this->sellbtn->Text = L"Sell";
				 this->sellbtn->UseVisualStyleBackColor = true;
				 this->sellbtn->Click += gcnew System::EventHandler(this, &CashierUI::sellbtn_Click);
				 // 
				 // searchBox
				 // 
				 this->searchBox->Location = System::Drawing::Point(12, 43);
				 this->searchBox->Name = L"searchBox";
				 this->searchBox->Size = System::Drawing::Size(170, 26);
				 this->searchBox->TabIndex = 0;
				 this->searchBox->Enter += gcnew System::EventHandler(this, &CashierUI::selectAll);
				 this->searchBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &CashierUI::searchBox_KeyPress);
				 // 
				 // searchType
				 // 
				 this->searchType->BackColor = System::Drawing::SystemColors::Control;
				 this->searchType->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->searchType->CheckOnClick = true;
				 this->searchType->Font = (gcnew System::Drawing::Font(L"Calibri", 12));
				 this->searchType->FormattingEnabled = true;
				 this->searchType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Barcode", L"Name", L"Category", L"Manufacturer"});
				 this->searchType->Location = System::Drawing::Point(200, 16);
				 this->searchType->Name = L"searchType";
				 this->searchType->Size = System::Drawing::Size(151, 88);
				 this->searchType->TabIndex = 1;
				 this->searchType->SelectedIndexChanged += gcnew System::EventHandler(this, &CashierUI::searchType_TextClick);
				 // 
				 // searchgroup
				 // 
				 this->searchgroup->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->searchgroup->Controls->Add(this->restockbtn);
				 this->searchgroup->Controls->Add(this->gobtn);
				 this->searchgroup->Controls->Add(this->sellbtn);
				 this->searchgroup->Controls->Add(this->searchtxt);
				 this->searchgroup->Controls->Add(this->searchType);
				 this->searchgroup->Controls->Add(this->searchBox);
				 this->searchgroup->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
				 this->searchgroup->Location = System::Drawing::Point(0, 27);
				 this->searchgroup->Name = L"searchgroup";
				 this->searchgroup->Size = System::Drawing::Size(778, 106);
				 this->searchgroup->TabIndex = 0;
				 this->searchgroup->TabStop = false;
				 this->searchgroup->Text = L"Search";
				 // 
				 // gobtn
				 // 
				 this->gobtn->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->gobtn->ForeColor = System::Drawing::SystemColors::ButtonFace;
				 this->gobtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"gobtn.Image")));
				 this->gobtn->Location = System::Drawing::Point(12, 73);
				 this->gobtn->Name = L"gobtn";
				 this->gobtn->Size = System::Drawing::Size(170, 29);
				 this->gobtn->TabIndex = 2;
				 this->gobtn->Text = L"GO";
				 this->gobtn->UseVisualStyleBackColor = true;
				 this->gobtn->Click += gcnew System::EventHandler(this, &CashierUI::gobtn_Click);
				 // 
				 // searchtxt
				 // 
				 this->searchtxt->AutoSize = true;
				 this->searchtxt->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->searchtxt->ForeColor = System::Drawing::SystemColors::HotTrack;
				 this->searchtxt->Location = System::Drawing::Point(12, 21);
				 this->searchtxt->Name = L"searchtxt";
				 this->searchtxt->Size = System::Drawing::Size(131, 19);
				 this->searchtxt->TabIndex = 19;
				 this->searchtxt->Text = L"Enter search string";
				 // 
				 // resultsListView
				 // 
				 this->resultsListView->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->resultsListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->nameCol, this->categoryCol, 
					 this->manufacturerCol, this->barcodeCol});
				 this->resultsListView->FullRowSelect = true;
				 this->resultsListView->Location = System::Drawing::Point(364, 161);
				 this->resultsListView->MultiSelect = false;
				 this->resultsListView->Name = L"resultsListView";
				 this->resultsListView->Size = System::Drawing::Size(408, 250);
				 this->resultsListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
				 this->resultsListView->TabIndex = 14;
				 this->resultsListView->TileSize = System::Drawing::Size(168, 15);
				 this->resultsListView->UseCompatibleStateImageBehavior = false;
				 this->resultsListView->View = System::Windows::Forms::View::Details;
				 this->resultsListView->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &CashierUI::resultsListView_ColumnClick);
				 this->resultsListView->SelectedIndexChanged += gcnew System::EventHandler(this, &CashierUI::resultsListView_SelectedIndexChanged);
				 // 
				 // nameCol
				 // 
				 this->nameCol->Text = L"Name";
				 this->nameCol->Width = 170;
				 // 
				 // categoryCol
				 // 
				 this->categoryCol->Text = L"Category";
				 this->categoryCol->Width = 78;
				 // 
				 // manufacturerCol
				 // 
				 this->manufacturerCol->Text = L"Manufacturer";
				 this->manufacturerCol->Width = 79;
				 // 
				 // barcodeCol
				 // 
				 this->barcodeCol->Text = L"Barcode";
				 // 
				 // resultgrp
				 // 
				 this->resultgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->resultgrp->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(0)));
				 this->resultgrp->Location = System::Drawing::Point(358, 137);
				 this->resultgrp->Name = L"resultgrp";
				 this->resultgrp->Size = System::Drawing::Size(420, 280);
				 this->resultgrp->TabIndex = 16;
				 this->resultgrp->TabStop = false;
				 this->resultgrp->Text = L"Results";
				 // 
				 // CashierUI
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(784, 442);
				 this->Controls->Add(this->resultsListView);
				 this->Controls->Add(this->resultgrp);
				 this->Controls->Add(this->productgrp);
				 this->Controls->Add(this->searchgroup);
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"CashierUI";
				 this->Text = L"CEG ICMS - Cashier";
				 this->Load += gcnew System::EventHandler(this, &CashierUI::CashierUI_Load);
				 this->Controls->SetChildIndex(this->searchgroup, 0);
				 this->Controls->SetChildIndex(this->productgrp, 0);
				 this->Controls->SetChildIndex(this->resultgrp, 0);
				 this->Controls->SetChildIndex(this->resultsListView, 0);
				 this->Controls->SetChildIndex(this->backgroundWorkerCancelBtn, 0);
				 this->productgrp->ResumeLayout(false);
				 this->productgrp->PerformLayout();
				 this->searchgroup->ResumeLayout(false);
				 this->searchgroup->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	protected:
		virtual void switchUIViews() override;
		virtual void backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) override;
	private:
		void CashierUI_Load(System::Object^  sender, System::EventArgs^  e);
		void searchType_TextClick(System::Object^  sender, System::EventArgs^  e);
		void searchBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void selectAll(System::Object^  sender, System::EventArgs^  e);
		void gobtn_Click(System::Object^  sender, System::EventArgs^  e);
		void updateFields(int i);
		void updateResults();
		void backgroundWorkerFillResults_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		void backgroundWorkerFillResults_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		void resultsListView_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);
		void resultsListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		bool btn_Click (Product*& product);
		void restockbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void sellbtn_Click(System::Object^  sender, System::EventArgs^  e) ;
	};
}
