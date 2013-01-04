#pragma once
#include "MainUI.h"
#include "ProductModUI.h"
#include "ListViewItemComparer.h"

namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ManagerUI
	/// UI Form for Manager Mode
	/// </summary>
	public ref class ManagerUI : public MainUI
	{
	public:
		ManagerUI(int* next, string* curUser, Inventory* inv, Password* pwDB) : MainUI(next,curUser,inv,pwDB)
		{
			invList = new vector<Product*>;
			manuList = new vector<pair<string,double>>;
			revenueList = new vector<pair<Product*,double>>;
			accountsList = new vector<pair<int,string>>;
			user = curUser;
			InitializeComponent();
		}

	protected:
		~ManagerUI()
		{
			delete revenueList;
			delete invList;
			if (components)
			{
				delete components;
			}
		}
	private:
		vector<pair<int,string>>* accountsList;
		vector<pair<Product*,double>>* revenueList;
		vector<pair<string,double>>* manuList;
		vector<Product*>* invList;
		string *user;
		System::ComponentModel::IContainer^  components;


#pragma region WindowsFormDeclarationRegion		
		System::Windows::Forms::TabControl^  tabControl;
		System::Windows::Forms::TabPage^  tabPageModInv;
		System::Windows::Forms::TabPage^  tabPageTopPrd;
		System::Windows::Forms::TabPage^  tabPageTopManu;
		System::Windows::Forms::GroupBox^  resultgrpPrd;
		System::Windows::Forms::GroupBox^  searchgrpPrd;
		System::Windows::Forms::Label^  label2;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::Label^  label3;
		System::Windows::Forms::ListView^  resultsListViewPrd;
		System::Windows::Forms::ColumnHeader^  barcodeCol;
		System::Windows::Forms::ColumnHeader^  nameCol;
		System::Windows::Forms::ColumnHeader^  categoryCol;
		System::Windows::Forms::ColumnHeader^  manufacturerCol;
		System::Windows::Forms::ColumnHeader^  priceCol;
		System::Windows::Forms::ColumnHeader^  discountCol;
		System::Windows::Forms::ColumnHeader^  stocksoldCol;
		System::Windows::Forms::ColumnHeader^  numleftCol;
		System::Windows::Forms::ColumnHeader^  expiryCol;
		System::Windows::Forms::ColumnHeader^  revenueCol;
		System::Windows::Forms::GroupBox^  searchgrpManu;
		System::Windows::Forms::CheckBox^  manuFilterCheck;
		System::Windows::Forms::Label^  label6;
		System::Windows::Forms::RadioButton^  manuFilterBtn;
		System::Windows::Forms::RadioButton^  catFilterBtn;
		System::Windows::Forms::Button^  searchPrdBtn;
		System::Windows::Forms::GroupBox^  resultgrpInv;
		System::Windows::Forms::ListView^  resultsListViewInv;
		System::Windows::Forms::ColumnHeader^  nameCol1;
		System::Windows::Forms::ColumnHeader^  categoryCol1;
		System::Windows::Forms::ColumnHeader^  manufacturerCol1;
		System::Windows::Forms::ColumnHeader^  priceCol1;
		System::Windows::Forms::ColumnHeader^  discountCol1;
		System::Windows::Forms::ColumnHeader^  numleftCol1;
		System::Windows::Forms::ColumnHeader^  expiryCol1;
		System::Windows::Forms::ColumnHeader^  barcodeCol1;
		System::Windows::Forms::GroupBox^  searchgrpInv;
		System::Windows::Forms::Button^  searchBtn;
		System::Windows::Forms::Label^  label7;
		System::Windows::Forms::CheckedListBox^  searchType;
		System::Windows::Forms::Label^  label4;
		System::ComponentModel::BackgroundWorker^  backgroundWorkerFillResults;
		System::Windows::Forms::TextBox^  filterBox;
		System::Windows::Forms::TextBox^  manuFilterBox;
		System::Windows::Forms::TextBox^  numTopBox;
		System::Windows::Forms::TextBox^  numTopManuBox;
		System::Windows::Forms::TextBox^  searchBox;
		System::Windows::Forms::ColumnHeader^  stocksoldCol1;
		System::Windows::Forms::GroupBox^  groupBox1;
		System::Windows::Forms::ListView^  resultsListViewManu;
		System::Windows::Forms::ColumnHeader^  manuCol;
		System::Windows::Forms::ColumnHeader^  revCol;
		System::Windows::Forms::ContextMenuStrip^  resultContextMenu;
		System::Windows::Forms::ToolStripMenuItem^  addProductToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  editProductToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  deleteProductToolStripMenuItem;
		System::Windows::Forms::TabPage^  tabPageUserAcc;
		System::Windows::Forms::GroupBox^  searchaccgrp;
		System::Windows::Forms::TextBox^  searchIDbox;
		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::Label^  label5;
		System::Windows::Forms::GroupBox^  accountsgrp;
		System::Windows::Forms::ListView^  resultsListViewAcc;
		System::Windows::Forms::ColumnHeader^  accessCol;
		System::Windows::Forms::ColumnHeader^  userIDCol;
		System::Windows::Forms::GroupBox^  addgrp;
		System::Windows::Forms::MaskedTextBox^  passwordbox;
		System::Windows::Forms::TextBox^  userIDbox;
		System::Windows::Forms::Label^  label9;
		System::Windows::Forms::Label^  label8;
		System::Windows::Forms::Button^  searchidbtn;
		System::Windows::Forms::GroupBox^  databasegrp;
		System::Windows::Forms::Label^  label10;
		System::Windows::Forms::Button^  addaccountbtn;
		System::Windows::Forms::RadioButton^  radiobtnManager;
		System::Windows::Forms::RadioButton^  radiobtnCashier;
		System::Windows::Forms::Button^  savedbbtn;
		System::Windows::Forms::Button^  cleardbbtn;
		System::Windows::Forms::ContextMenuStrip^  accountsContextMenu;
		System::Windows::Forms::ToolStripMenuItem^  deleteAccountToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  perishableToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  nonPerishableToolStripMenuItem;
		System::Windows::Forms::TabPage^  tabPageBatchJob;
		System::Windows::Forms::GroupBox^  addbatchjobgrp;
		System::Windows::Forms::Label^  numjobsaddedtxt;
		System::Windows::Forms::TabControl^  tabcontrol1;
		System::Windows::Forms::TabPage^  addtab;
		System::Windows::Forms::Button^  addbtn;
		System::Windows::Forms::Label^  label12;
		System::Windows::Forms::GroupBox^  productgrp;
		System::Windows::Forms::Label^  manufacturertxt;
		System::Windows::Forms::TextBox^  numStockAdd;
		System::Windows::Forms::Label^  nametxt;
		System::Windows::Forms::Label^  stocktxt;
		System::Windows::Forms::TextBox^  nameAdd;
		System::Windows::Forms::TextBox^  manufacturerAdd;
		System::Windows::Forms::Label^  categorytxt;
		System::Windows::Forms::TextBox^  categoryAdd;
		System::Windows::Forms::TextBox^  priceAdd;
		System::Windows::Forms::Label^  barcodetxt;
		System::Windows::Forms::Label^  pricetxt;
		System::Windows::Forms::TextBox^  barcodeAdd;
		System::Windows::Forms::TabPage^  deletetab;
		System::Windows::Forms::Label^  deleteproducttxt;
		System::Windows::Forms::TextBox^  barcodeDelete;
		System::Windows::Forms::Label^  label13;
		System::Windows::Forms::TabPage^  restocktab;
		System::Windows::Forms::Label^  label14;
		System::Windows::Forms::TextBox^  numAddRestock;
		System::Windows::Forms::Label^  restocktxt;
		System::Windows::Forms::TextBox^  barcodeRestock;
		System::Windows::Forms::Label^  restockbarcodetxt;
		System::Windows::Forms::TabPage^  disposetab;
		System::Windows::Forms::Label^  disposetxt;
		System::Windows::Forms::TextBox^  barcodeDispose;
		System::Windows::Forms::Label^  disposebarcodetxt;
		System::Windows::Forms::TabPage^  disposealltab;
		System::Windows::Forms::Label^  disposealltxt;
		System::Windows::Forms::TabPage^  saletab;
		System::Windows::Forms::Label^  saletxt;
		System::Windows::Forms::TextBox^  numSoldSale;
		System::Windows::Forms::Label^  salenumtxt;
		System::Windows::Forms::TextBox^  barcodeSale;
		System::Windows::Forms::Label^  salebarcodetxt;
		System::Windows::Forms::TabPage^  discounttab;
		System::Windows::Forms::Label^  changediscounttxt;
		System::Windows::Forms::TextBox^  discountDiscount;
		System::Windows::Forms::Label^  discounttxt;
		System::Windows::Forms::TextBox^  daysLeftDiscount;
		System::Windows::Forms::Label^  dayslefttxt;
		System::Windows::Forms::TabPage^  restockMtab;
		System::Windows::Forms::Label^  restockMtxt;
		System::Windows::Forms::TextBox^  numAddRestockManufacturer;
		System::Windows::Forms::Label^  restockMstocktxt;
		System::Windows::Forms::Label^  restockMmanutxt;
		System::Windows::Forms::TextBox^  manufacturerRestockManufacturer;
		System::Windows::Forms::TabPage^  restockCtab;
		System::Windows::Forms::Label^  label15;
		System::Windows::Forms::TextBox^  categoryRestockCategory;
		System::Windows::Forms::Label^  label26;
		System::Windows::Forms::TextBox^  numAddRestockCategory;
		System::Windows::Forms::Label^  label27;
		System::Windows::Forms::TabPage^  tabPage11;
		System::Windows::Forms::Label^  restockLtxt;
		System::Windows::Forms::TextBox^  numAddRestockLeft;
		System::Windows::Forms::Label^  restockLfinalstocktxt;
		System::Windows::Forms::TextBox^  leftRestockLeft;
		System::Windows::Forms::Label^  restockLcurrstocktxt;
		System::Windows::Forms::TextBox^  numjobsaddedbox;
		System::Windows::Forms::Button^  finishbtn;
		System::Windows::Forms::Button^  searchManuBtn;

#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPageModInv = (gcnew System::Windows::Forms::TabPage());
			this->resultgrpInv = (gcnew System::Windows::Forms::GroupBox());
			this->resultsListViewInv = (gcnew System::Windows::Forms::ListView());
			this->nameCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->categoryCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->manufacturerCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->priceCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->discountCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stocksoldCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->numleftCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->expiryCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->barcodeCol1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->resultContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->addProductToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->perishableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->nonPerishableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editProductToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteProductToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchgrpInv = (gcnew System::Windows::Forms::GroupBox());
			this->searchBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->searchType = (gcnew System::Windows::Forms::CheckedListBox());
			this->searchBtn = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tabPageTopPrd = (gcnew System::Windows::Forms::TabPage());
			this->resultgrpPrd = (gcnew System::Windows::Forms::GroupBox());
			this->resultsListViewPrd = (gcnew System::Windows::Forms::ListView());
			this->revenueCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->categoryCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->manufacturerCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->priceCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->discountCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->stocksoldCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->numleftCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->expiryCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->barcodeCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->searchgrpPrd = (gcnew System::Windows::Forms::GroupBox());
			this->numTopBox = (gcnew System::Windows::Forms::TextBox());
			this->filterBox = (gcnew System::Windows::Forms::TextBox());
			this->manuFilterBtn = (gcnew System::Windows::Forms::RadioButton());
			this->catFilterBtn = (gcnew System::Windows::Forms::RadioButton());
			this->searchPrdBtn = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPageTopManu = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->resultsListViewManu = (gcnew System::Windows::Forms::ListView());
			this->revCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->manuCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->searchgrpManu = (gcnew System::Windows::Forms::GroupBox());
			this->numTopManuBox = (gcnew System::Windows::Forms::TextBox());
			this->manuFilterBox = (gcnew System::Windows::Forms::TextBox());
			this->searchManuBtn = (gcnew System::Windows::Forms::Button());
			this->manuFilterCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tabPageBatchJob = (gcnew System::Windows::Forms::TabPage());
			this->addbtn = (gcnew System::Windows::Forms::Button());
			this->addbatchjobgrp = (gcnew System::Windows::Forms::GroupBox());
			this->tabcontrol1 = (gcnew System::Windows::Forms::TabControl());
			this->addtab = (gcnew System::Windows::Forms::TabPage());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->productgrp = (gcnew System::Windows::Forms::GroupBox());
			this->manufacturertxt = (gcnew System::Windows::Forms::Label());
			this->numStockAdd = (gcnew System::Windows::Forms::TextBox());
			this->nametxt = (gcnew System::Windows::Forms::Label());
			this->stocktxt = (gcnew System::Windows::Forms::Label());
			this->nameAdd = (gcnew System::Windows::Forms::TextBox());
			this->manufacturerAdd = (gcnew System::Windows::Forms::TextBox());
			this->categorytxt = (gcnew System::Windows::Forms::Label());
			this->categoryAdd = (gcnew System::Windows::Forms::TextBox());
			this->priceAdd = (gcnew System::Windows::Forms::TextBox());
			this->barcodetxt = (gcnew System::Windows::Forms::Label());
			this->pricetxt = (gcnew System::Windows::Forms::Label());
			this->barcodeAdd = (gcnew System::Windows::Forms::TextBox());
			this->deletetab = (gcnew System::Windows::Forms::TabPage());
			this->deleteproducttxt = (gcnew System::Windows::Forms::Label());
			this->barcodeDelete = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->restocktab = (gcnew System::Windows::Forms::TabPage());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->numAddRestock = (gcnew System::Windows::Forms::TextBox());
			this->restocktxt = (gcnew System::Windows::Forms::Label());
			this->barcodeRestock = (gcnew System::Windows::Forms::TextBox());
			this->restockbarcodetxt = (gcnew System::Windows::Forms::Label());
			this->disposetab = (gcnew System::Windows::Forms::TabPage());
			this->disposetxt = (gcnew System::Windows::Forms::Label());
			this->barcodeDispose = (gcnew System::Windows::Forms::TextBox());
			this->disposebarcodetxt = (gcnew System::Windows::Forms::Label());
			this->disposealltab = (gcnew System::Windows::Forms::TabPage());
			this->disposealltxt = (gcnew System::Windows::Forms::Label());
			this->saletab = (gcnew System::Windows::Forms::TabPage());
			this->saletxt = (gcnew System::Windows::Forms::Label());
			this->numSoldSale = (gcnew System::Windows::Forms::TextBox());
			this->salenumtxt = (gcnew System::Windows::Forms::Label());
			this->barcodeSale = (gcnew System::Windows::Forms::TextBox());
			this->salebarcodetxt = (gcnew System::Windows::Forms::Label());
			this->discounttab = (gcnew System::Windows::Forms::TabPage());
			this->changediscounttxt = (gcnew System::Windows::Forms::Label());
			this->discountDiscount = (gcnew System::Windows::Forms::TextBox());
			this->discounttxt = (gcnew System::Windows::Forms::Label());
			this->daysLeftDiscount = (gcnew System::Windows::Forms::TextBox());
			this->dayslefttxt = (gcnew System::Windows::Forms::Label());
			this->restockMtab = (gcnew System::Windows::Forms::TabPage());
			this->restockMtxt = (gcnew System::Windows::Forms::Label());
			this->numAddRestockManufacturer = (gcnew System::Windows::Forms::TextBox());
			this->restockMstocktxt = (gcnew System::Windows::Forms::Label());
			this->restockMmanutxt = (gcnew System::Windows::Forms::Label());
			this->manufacturerRestockManufacturer = (gcnew System::Windows::Forms::TextBox());
			this->restockCtab = (gcnew System::Windows::Forms::TabPage());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->categoryRestockCategory = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->numAddRestockCategory = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->tabPage11 = (gcnew System::Windows::Forms::TabPage());
			this->restockLtxt = (gcnew System::Windows::Forms::Label());
			this->numAddRestockLeft = (gcnew System::Windows::Forms::TextBox());
			this->restockLfinalstocktxt = (gcnew System::Windows::Forms::Label());
			this->leftRestockLeft = (gcnew System::Windows::Forms::TextBox());
			this->restockLcurrstocktxt = (gcnew System::Windows::Forms::Label());
			this->numjobsaddedtxt = (gcnew System::Windows::Forms::Label());
			this->finishbtn = (gcnew System::Windows::Forms::Button());
			this->numjobsaddedbox = (gcnew System::Windows::Forms::TextBox());
			this->tabPageUserAcc = (gcnew System::Windows::Forms::TabPage());
			this->databasegrp = (gcnew System::Windows::Forms::GroupBox());
			this->savedbbtn = (gcnew System::Windows::Forms::Button());
			this->cleardbbtn = (gcnew System::Windows::Forms::Button());
			this->addgrp = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->addaccountbtn = (gcnew System::Windows::Forms::Button());
			this->radiobtnManager = (gcnew System::Windows::Forms::RadioButton());
			this->radiobtnCashier = (gcnew System::Windows::Forms::RadioButton());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->passwordbox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->userIDbox = (gcnew System::Windows::Forms::TextBox());
			this->searchaccgrp = (gcnew System::Windows::Forms::GroupBox());
			this->searchidbtn = (gcnew System::Windows::Forms::Button());
			this->searchIDbox = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->accountsgrp = (gcnew System::Windows::Forms::GroupBox());
			this->resultsListViewAcc = (gcnew System::Windows::Forms::ListView());
			this->accessCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->userIDCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->accountsContextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->deleteAccountToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->backgroundWorkerFillResults = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabControl->SuspendLayout();
			this->tabPageModInv->SuspendLayout();
			this->resultgrpInv->SuspendLayout();
			this->resultContextMenu->SuspendLayout();
			this->searchgrpInv->SuspendLayout();
			this->tabPageTopPrd->SuspendLayout();
			this->resultgrpPrd->SuspendLayout();
			this->searchgrpPrd->SuspendLayout();
			this->tabPageTopManu->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->searchgrpManu->SuspendLayout();
			this->tabPageBatchJob->SuspendLayout();
			this->addbatchjobgrp->SuspendLayout();
			this->tabcontrol1->SuspendLayout();
			this->addtab->SuspendLayout();
			this->productgrp->SuspendLayout();
			this->deletetab->SuspendLayout();
			this->restocktab->SuspendLayout();
			this->disposetab->SuspendLayout();
			this->disposealltab->SuspendLayout();
			this->saletab->SuspendLayout();
			this->discounttab->SuspendLayout();
			this->restockMtab->SuspendLayout();
			this->restockCtab->SuspendLayout();
			this->tabPage11->SuspendLayout();
			this->tabPageUserAcc->SuspendLayout();
			this->databasegrp->SuspendLayout();
			this->addgrp->SuspendLayout();
			this->searchaccgrp->SuspendLayout();
			this->accountsgrp->SuspendLayout();
			this->accountsContextMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPageModInv);
			this->tabControl->Controls->Add(this->tabPageTopPrd);
			this->tabControl->Controls->Add(this->tabPageTopManu);
			this->tabControl->Controls->Add(this->tabPageBatchJob);
			this->tabControl->Controls->Add(this->tabPageUserAcc);
			this->tabControl->Location = System::Drawing::Point(0, 27);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(785, 394);
			this->tabControl->TabIndex = 99;
			this->tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerUI::tabControl_SelectedIndexChanged);
			this->tabControl->Enter += gcnew System::EventHandler(this, &ManagerUI::tabControl_Enter);
			// 
			// tabPageModInv
			// 
			this->tabPageModInv->Controls->Add(this->resultgrpInv);
			this->tabPageModInv->Controls->Add(this->searchgrpInv);
			this->tabPageModInv->Location = System::Drawing::Point(4, 22);
			this->tabPageModInv->Name = L"tabPageModInv";
			this->tabPageModInv->Padding = System::Windows::Forms::Padding(3);
			this->tabPageModInv->Size = System::Drawing::Size(777, 368);
			this->tabPageModInv->TabIndex = 0;
			this->tabPageModInv->Text = L"Inventory";
			this->tabPageModInv->UseVisualStyleBackColor = true;
			// 
			// resultgrpInv
			// 
			this->resultgrpInv->Controls->Add(this->resultsListViewInv);
			this->resultgrpInv->Location = System::Drawing::Point(8, 115);
			this->resultgrpInv->Name = L"resultgrpInv";
			this->resultgrpInv->Size = System::Drawing::Size(762, 244);
			this->resultgrpInv->TabIndex = 1;
			this->resultgrpInv->TabStop = false;
			this->resultgrpInv->Text = L"Results";
			// 
			// resultsListViewInv
			// 
			this->resultsListViewInv->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->resultsListViewInv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {this->nameCol1, 
				this->categoryCol1, this->manufacturerCol1, this->priceCol1, this->discountCol1, this->stocksoldCol1, this->numleftCol1, this->expiryCol1, 
				this->barcodeCol1});
			this->resultsListViewInv->ContextMenuStrip = this->resultContextMenu;
			this->resultsListViewInv->FullRowSelect = true;
			this->resultsListViewInv->Location = System::Drawing::Point(6, 16);
			this->resultsListViewInv->Name = L"resultsListViewInv";
			this->resultsListViewInv->Size = System::Drawing::Size(750, 222);
			this->resultsListViewInv->TabIndex = 3;
			this->resultsListViewInv->TileSize = System::Drawing::Size(168, 15);
			this->resultsListViewInv->UseCompatibleStateImageBehavior = false;
			this->resultsListViewInv->View = System::Windows::Forms::View::Details;
			this->resultsListViewInv->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &ManagerUI::resultsListViewInv_ColumnClick);
			this->resultsListViewInv->DoubleClick += gcnew System::EventHandler(this, &ManagerUI::resultsListViewInv_DoubleClick);
			// 
			// nameCol1
			// 
			this->nameCol1->Text = L"Name";
			this->nameCol1->Width = 143;
			// 
			// categoryCol1
			// 
			this->categoryCol1->Text = L"Category";
			this->categoryCol1->Width = 101;
			// 
			// manufacturerCol1
			// 
			this->manufacturerCol1->Text = L"Manufacturer";
			this->manufacturerCol1->Width = 106;
			// 
			// priceCol1
			// 
			this->priceCol1->Text = L"Price";
			this->priceCol1->Width = 61;
			// 
			// discountCol1
			// 
			this->discountCol1->Text = L"Discount";
			this->discountCol1->Width = 55;
			// 
			// stocksoldCol1
			// 
			this->stocksoldCol1->Text = L"Sold";
			this->stocksoldCol1->Width = 43;
			// 
			// numleftCol1
			// 
			this->numleftCol1->Text = L"Stock";
			this->numleftCol1->Width = 50;
			// 
			// expiryCol1
			// 
			this->expiryCol1->Text = L"Expiry";
			this->expiryCol1->Width = 90;
			// 
			// barcodeCol1
			// 
			this->barcodeCol1->Text = L"Barcode";
			this->barcodeCol1->Width = 93;
			// 
			// resultContextMenu
			// 
			this->resultContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->addProductToolStripMenuItem, 
				this->editProductToolStripMenuItem, this->deleteProductToolStripMenuItem});
			this->resultContextMenu->Name = L"contextMenuStrip1";
			this->resultContextMenu->Size = System::Drawing::Size(153, 70);
			this->resultContextMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ManagerUI::resultContextMenu_Opening);
			// 
			// addProductToolStripMenuItem
			// 
			this->addProductToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->perishableToolStripMenuItem, 
				this->nonPerishableToolStripMenuItem});
			this->addProductToolStripMenuItem->Name = L"addProductToolStripMenuItem";
			this->addProductToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->addProductToolStripMenuItem->Text = L"Add Product";
			// 
			// perishableToolStripMenuItem
			// 
			this->perishableToolStripMenuItem->Name = L"perishableToolStripMenuItem";
			this->perishableToolStripMenuItem->Size = System::Drawing::Size(156, 22);
			this->perishableToolStripMenuItem->Text = L"Perishable";
			this->perishableToolStripMenuItem->Click += gcnew System::EventHandler(this, &ManagerUI::perishableToolStripMenuItem_Click);
			// 
			// nonPerishableToolStripMenuItem
			// 
			this->nonPerishableToolStripMenuItem->Name = L"nonPerishableToolStripMenuItem";
			this->nonPerishableToolStripMenuItem->Size = System::Drawing::Size(156, 22);
			this->nonPerishableToolStripMenuItem->Text = L"Non-Perishable";
			this->nonPerishableToolStripMenuItem->Click += gcnew System::EventHandler(this, &ManagerUI::nonPerishableToolStripMenuItem_Click);
			// 
			// editProductToolStripMenuItem
			// 
			this->editProductToolStripMenuItem->Name = L"editProductToolStripMenuItem";
			this->editProductToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->editProductToolStripMenuItem->Text = L"Edit Product";
			this->editProductToolStripMenuItem->Visible = false;
			this->editProductToolStripMenuItem->Click += gcnew System::EventHandler(this, &ManagerUI::editProductToolStripMenuItem_Click);
			// 
			// deleteProductToolStripMenuItem
			// 
			this->deleteProductToolStripMenuItem->Name = L"deleteProductToolStripMenuItem";
			this->deleteProductToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->deleteProductToolStripMenuItem->Text = L"Delete Product";
			this->deleteProductToolStripMenuItem->Visible = false;
			this->deleteProductToolStripMenuItem->Click += gcnew System::EventHandler(this, &ManagerUI::deleteProductToolStripMenuItem_Click);
			// 
			// searchgrpInv
			// 
			this->searchgrpInv->Controls->Add(this->searchBox);
			this->searchgrpInv->Controls->Add(this->label4);
			this->searchgrpInv->Controls->Add(this->searchType);
			this->searchgrpInv->Controls->Add(this->searchBtn);
			this->searchgrpInv->Controls->Add(this->label7);
			this->searchgrpInv->Location = System::Drawing::Point(8, 1);
			this->searchgrpInv->Name = L"searchgrpInv";
			this->searchgrpInv->Size = System::Drawing::Size(762, 109);
			this->searchgrpInv->TabIndex = 0;
			this->searchgrpInv->TabStop = false;
			this->searchgrpInv->Text = L"Search";
			// 
			// searchBox
			// 
			this->searchBox->Location = System::Drawing::Point(26, 49);
			this->searchBox->Name = L"searchBox";
			this->searchBox->Size = System::Drawing::Size(162, 20);
			this->searchBox->TabIndex = 0;
			this->searchBox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->searchBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::searchBox_KeyPress);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(220, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Filter by...";
			// 
			// searchType
			// 
			this->searchType->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->searchType->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->searchType->CheckOnClick = true;
			this->searchType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->searchType->FormattingEnabled = true;
			this->searchType->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Barcode", L"Name", L"Category", L"Manufacturer"});
			this->searchType->Location = System::Drawing::Point(223, 38);
			this->searchType->Name = L"searchType";
			this->searchType->Size = System::Drawing::Size(157, 60);
			this->searchType->TabIndex = 2;
			this->searchType->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerUI::searchType_TextClick);
			// 
			// searchBtn
			// 
			this->searchBtn->Location = System::Drawing::Point(26, 75);
			this->searchBtn->Name = L"searchBtn";
			this->searchBtn->Size = System::Drawing::Size(162, 23);
			this->searchBtn->TabIndex = 1;
			this->searchBtn->Text = L"Search";
			this->searchBtn->UseVisualStyleBackColor = true;
			this->searchBtn->Click += gcnew System::EventHandler(this, &ManagerUI::searchBtn_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(23, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(95, 13);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Enter search string";
			// 
			// tabPageTopPrd
			// 
			this->tabPageTopPrd->Controls->Add(this->resultgrpPrd);
			this->tabPageTopPrd->Controls->Add(this->searchgrpPrd);
			this->tabPageTopPrd->Location = System::Drawing::Point(4, 22);
			this->tabPageTopPrd->Name = L"tabPageTopPrd";
			this->tabPageTopPrd->Padding = System::Windows::Forms::Padding(3);
			this->tabPageTopPrd->Size = System::Drawing::Size(776, 370);
			this->tabPageTopPrd->TabIndex = 1;
			this->tabPageTopPrd->Text = L"Top Products";
			this->tabPageTopPrd->UseVisualStyleBackColor = true;
			// 
			// resultgrpPrd
			// 
			this->resultgrpPrd->Controls->Add(this->resultsListViewPrd);
			this->resultgrpPrd->Location = System::Drawing::Point(8, 115);
			this->resultgrpPrd->Name = L"resultgrpPrd";
			this->resultgrpPrd->Size = System::Drawing::Size(762, 244);
			this->resultgrpPrd->TabIndex = 3;
			this->resultgrpPrd->TabStop = false;
			this->resultgrpPrd->Text = L"Results";
			// 
			// resultsListViewPrd
			// 
			this->resultsListViewPrd->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->resultsListViewPrd->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(10) {this->revenueCol, 
				this->nameCol, this->categoryCol, this->manufacturerCol, this->priceCol, this->discountCol, this->stocksoldCol, this->numleftCol, 
				this->expiryCol, this->barcodeCol});
			this->resultsListViewPrd->FullRowSelect = true;
			this->resultsListViewPrd->Location = System::Drawing::Point(6, 16);
			this->resultsListViewPrd->MultiSelect = false;
			this->resultsListViewPrd->Name = L"resultsListViewPrd";
			this->resultsListViewPrd->Size = System::Drawing::Size(750, 222);
			this->resultsListViewPrd->TabIndex = 5;
			this->resultsListViewPrd->TileSize = System::Drawing::Size(168, 15);
			this->resultsListViewPrd->UseCompatibleStateImageBehavior = false;
			this->resultsListViewPrd->View = System::Windows::Forms::View::Details;
			this->resultsListViewPrd->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &ManagerUI::resultsListViewPrd_ColumnClick);
			// 
			// revenueCol
			// 
			this->revenueCol->Text = L"Revenue";
			this->revenueCol->Width = 68;
			// 
			// nameCol
			// 
			this->nameCol->Text = L"Name";
			this->nameCol->Width = 143;
			// 
			// categoryCol
			// 
			this->categoryCol->Text = L"Category";
			this->categoryCol->Width = 91;
			// 
			// manufacturerCol
			// 
			this->manufacturerCol->Text = L"Manufacturer";
			this->manufacturerCol->Width = 92;
			// 
			// priceCol
			// 
			this->priceCol->Text = L"Price";
			this->priceCol->Width = 65;
			// 
			// discountCol
			// 
			this->discountCol->Text = L"Discount";
			// 
			// stocksoldCol
			// 
			this->stocksoldCol->Text = L"Sold";
			this->stocksoldCol->Width = 43;
			// 
			// numleftCol
			// 
			this->numleftCol->Text = L"Stock";
			this->numleftCol->Width = 45;
			// 
			// expiryCol
			// 
			this->expiryCol->Text = L"Expiry";
			this->expiryCol->Width = 65;
			// 
			// barcodeCol
			// 
			this->barcodeCol->Text = L"Barcode";
			this->barcodeCol->Width = 72;
			// 
			// searchgrpPrd
			// 
			this->searchgrpPrd->Controls->Add(this->numTopBox);
			this->searchgrpPrd->Controls->Add(this->filterBox);
			this->searchgrpPrd->Controls->Add(this->manuFilterBtn);
			this->searchgrpPrd->Controls->Add(this->catFilterBtn);
			this->searchgrpPrd->Controls->Add(this->searchPrdBtn);
			this->searchgrpPrd->Controls->Add(this->label3);
			this->searchgrpPrd->Controls->Add(this->label2);
			this->searchgrpPrd->Controls->Add(this->label1);
			this->searchgrpPrd->Location = System::Drawing::Point(8, 1);
			this->searchgrpPrd->Name = L"searchgrpPrd";
			this->searchgrpPrd->Size = System::Drawing::Size(762, 109);
			this->searchgrpPrd->TabIndex = 2;
			this->searchgrpPrd->TabStop = false;
			this->searchgrpPrd->Text = L"Search";
			// 
			// numTopBox
			// 
			this->numTopBox->Location = System::Drawing::Point(26, 60);
			this->numTopBox->Name = L"numTopBox";
			this->numTopBox->Size = System::Drawing::Size(162, 20);
			this->numTopBox->TabIndex = 0;
			this->numTopBox->Text = L"1";
			this->numTopBox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->numTopBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::numTopBox_KeyPress);
			// 
			// filterBox
			// 
			this->filterBox->Location = System::Drawing::Point(323, 32);
			this->filterBox->Name = L"filterBox";
			this->filterBox->Size = System::Drawing::Size(144, 20);
			this->filterBox->TabIndex = 1;
			this->filterBox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->filterBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::filterBox_KeyPress);
			// 
			// manuFilterBtn
			// 
			this->manuFilterBtn->AutoCheck = false;
			this->manuFilterBtn->AutoSize = true;
			this->manuFilterBtn->Location = System::Drawing::Point(381, 61);
			this->manuFilterBtn->Name = L"manuFilterBtn";
			this->manuFilterBtn->Size = System::Drawing::Size(88, 17);
			this->manuFilterBtn->TabIndex = 3;
			this->manuFilterBtn->TabStop = true;
			this->manuFilterBtn->Text = L"Manufacturer";
			this->manuFilterBtn->UseVisualStyleBackColor = true;
			this->manuFilterBtn->Click += gcnew System::EventHandler(this, &ManagerUI::manuFilterBtn_Click);
			// 
			// catFilterBtn
			// 
			this->catFilterBtn->AutoCheck = false;
			this->catFilterBtn->AutoSize = true;
			this->catFilterBtn->Location = System::Drawing::Point(293, 61);
			this->catFilterBtn->Name = L"catFilterBtn";
			this->catFilterBtn->Size = System::Drawing::Size(67, 17);
			this->catFilterBtn->TabIndex = 2;
			this->catFilterBtn->TabStop = true;
			this->catFilterBtn->Text = L"Category";
			this->catFilterBtn->UseVisualStyleBackColor = true;
			this->catFilterBtn->Click += gcnew System::EventHandler(this, &ManagerUI::catFilterBtn_Click);
			// 
			// searchPrdBtn
			// 
			this->searchPrdBtn->Location = System::Drawing::Point(589, 32);
			this->searchPrdBtn->Name = L"searchPrdBtn";
			this->searchPrdBtn->Size = System::Drawing::Size(61, 48);
			this->searchPrdBtn->TabIndex = 4;
			this->searchPrdBtn->Text = L"Search";
			this->searchPrdBtn->UseVisualStyleBackColor = true;
			this->searchPrdBtn->Click += gcnew System::EventHandler(this, &ManagerUI::searchPrdBtn_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(473, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(27, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"by...";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(288, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Filter";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(165, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of top products to display";
			// 
			// tabPageTopManu
			// 
			this->tabPageTopManu->Controls->Add(this->groupBox1);
			this->tabPageTopManu->Controls->Add(this->searchgrpManu);
			this->tabPageTopManu->Location = System::Drawing::Point(4, 22);
			this->tabPageTopManu->Name = L"tabPageTopManu";
			this->tabPageTopManu->Size = System::Drawing::Size(776, 370);
			this->tabPageTopManu->TabIndex = 2;
			this->tabPageTopManu->Text = L"Top Manufacturers";
			this->tabPageTopManu->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->resultsListViewManu);
			this->groupBox1->Location = System::Drawing::Point(8, 116);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(762, 244);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Results";
			// 
			// resultsListViewManu
			// 
			this->resultsListViewManu->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->resultsListViewManu->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->revCol, 
				this->manuCol});
			this->resultsListViewManu->FullRowSelect = true;
			this->resultsListViewManu->Location = System::Drawing::Point(6, 16);
			this->resultsListViewManu->MultiSelect = false;
			this->resultsListViewManu->Name = L"resultsListViewManu";
			this->resultsListViewManu->Size = System::Drawing::Size(750, 222);
			this->resultsListViewManu->TabIndex = 5;
			this->resultsListViewManu->TileSize = System::Drawing::Size(168, 15);
			this->resultsListViewManu->UseCompatibleStateImageBehavior = false;
			this->resultsListViewManu->View = System::Windows::Forms::View::Details;
			this->resultsListViewManu->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &ManagerUI::resultsListViewManu_ColumnClick);
			// 
			// revCol
			// 
			this->revCol->Text = L"Total Revenue";
			this->revCol->Width = 106;
			// 
			// manuCol
			// 
			this->manuCol->Text = L"Manufacturer";
			this->manuCol->Width = 200;
			// 
			// searchgrpManu
			// 
			this->searchgrpManu->Controls->Add(this->numTopManuBox);
			this->searchgrpManu->Controls->Add(this->manuFilterBox);
			this->searchgrpManu->Controls->Add(this->searchManuBtn);
			this->searchgrpManu->Controls->Add(this->manuFilterCheck);
			this->searchgrpManu->Controls->Add(this->label6);
			this->searchgrpManu->Location = System::Drawing::Point(8, 1);
			this->searchgrpManu->Name = L"searchgrpManu";
			this->searchgrpManu->Size = System::Drawing::Size(762, 109);
			this->searchgrpManu->TabIndex = 4;
			this->searchgrpManu->TabStop = false;
			this->searchgrpManu->Text = L"Search";
			// 
			// numTopManuBox
			// 
			this->numTopManuBox->Location = System::Drawing::Point(26, 60);
			this->numTopManuBox->Name = L"numTopManuBox";
			this->numTopManuBox->Size = System::Drawing::Size(170, 20);
			this->numTopManuBox->TabIndex = 0;
			this->numTopManuBox->Text = L"1";
			this->numTopManuBox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->numTopManuBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::numTopManuBox_KeyPress);
			// 
			// manuFilterBox
			// 
			this->manuFilterBox->Location = System::Drawing::Point(293, 60);
			this->manuFilterBox->Name = L"manuFilterBox";
			this->manuFilterBox->Size = System::Drawing::Size(170, 20);
			this->manuFilterBox->TabIndex = 2;
			this->manuFilterBox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->manuFilterBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::manuFilterBox_KeyPress);
			// 
			// searchManuBtn
			// 
			this->searchManuBtn->Location = System::Drawing::Point(564, 32);
			this->searchManuBtn->Name = L"searchManuBtn";
			this->searchManuBtn->Size = System::Drawing::Size(61, 48);
			this->searchManuBtn->TabIndex = 3;
			this->searchManuBtn->Text = L"Search";
			this->searchManuBtn->UseVisualStyleBackColor = true;
			this->searchManuBtn->Click += gcnew System::EventHandler(this, &ManagerUI::searchManuBtn_Click);
			// 
			// manuFilterCheck
			// 
			this->manuFilterCheck->AutoSize = true;
			this->manuFilterCheck->Location = System::Drawing::Point(293, 35);
			this->manuFilterCheck->Name = L"manuFilterCheck";
			this->manuFilterCheck->Size = System::Drawing::Size(106, 17);
			this->manuFilterCheck->TabIndex = 1;
			this->manuFilterCheck->Text = L"Filter by category";
			this->manuFilterCheck->UseVisualStyleBackColor = true;
			this->manuFilterCheck->CheckStateChanged += gcnew System::EventHandler(this, &ManagerUI::manuCheckBox_CheckStateChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(23, 35);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(173, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Number of manufacturers to display";
			// 
			// tabPageBatchJob
			// 
			this->tabPageBatchJob->Controls->Add(this->addbtn);
			this->tabPageBatchJob->Controls->Add(this->addbatchjobgrp);
			this->tabPageBatchJob->Controls->Add(this->numjobsaddedtxt);
			this->tabPageBatchJob->Controls->Add(this->finishbtn);
			this->tabPageBatchJob->Controls->Add(this->numjobsaddedbox);
			this->tabPageBatchJob->Location = System::Drawing::Point(4, 22);
			this->tabPageBatchJob->Name = L"tabPageBatchJob";
			this->tabPageBatchJob->Size = System::Drawing::Size(776, 370);
			this->tabPageBatchJob->TabIndex = 4;
			this->tabPageBatchJob->Text = L"Batch Job";
			this->tabPageBatchJob->UseVisualStyleBackColor = true;
			// 
			// addbtn
			// 
			this->addbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->addbtn->Location = System::Drawing::Point(680, 152);
			this->addbtn->Name = L"addbtn";
			this->addbtn->Size = System::Drawing::Size(78, 50);
			this->addbtn->TabIndex = 1;
			this->addbtn->Text = L"Add Job";
			this->addbtn->UseVisualStyleBackColor = true;
			this->addbtn->Click += gcnew System::EventHandler(this, &ManagerUI::addbtn_Click);
			// 
			// addbatchjobgrp
			// 
			this->addbatchjobgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->addbatchjobgrp->Controls->Add(this->tabcontrol1);
			this->addbatchjobgrp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->addbatchjobgrp->Location = System::Drawing::Point(8, 26);
			this->addbatchjobgrp->Name = L"addbatchjobgrp";
			this->addbatchjobgrp->Size = System::Drawing::Size(666, 256);
			this->addbatchjobgrp->TabIndex = 0;
			this->addbatchjobgrp->TabStop = false;
			this->addbatchjobgrp->Text = L"Add Batch Job";
			// 
			// tabcontrol1
			// 
			this->tabcontrol1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->tabcontrol1->Controls->Add(this->addtab);
			this->tabcontrol1->Controls->Add(this->deletetab);
			this->tabcontrol1->Controls->Add(this->restocktab);
			this->tabcontrol1->Controls->Add(this->disposetab);
			this->tabcontrol1->Controls->Add(this->disposealltab);
			this->tabcontrol1->Controls->Add(this->saletab);
			this->tabcontrol1->Controls->Add(this->discounttab);
			this->tabcontrol1->Controls->Add(this->restockMtab);
			this->tabcontrol1->Controls->Add(this->restockCtab);
			this->tabcontrol1->Controls->Add(this->tabPage11);
			this->tabcontrol1->ItemSize = System::Drawing::Size(42, 20);
			this->tabcontrol1->Location = System::Drawing::Point(6, 22);
			this->tabcontrol1->Multiline = true;
			this->tabcontrol1->Name = L"tabcontrol1";
			this->tabcontrol1->SelectedIndex = 0;
			this->tabcontrol1->Size = System::Drawing::Size(652, 222);
			this->tabcontrol1->TabIndex = 0;
			// 
			// addtab
			// 
			this->addtab->Controls->Add(this->label12);
			this->addtab->Controls->Add(this->productgrp);
			this->addtab->Location = System::Drawing::Point(4, 44);
			this->addtab->Name = L"addtab";
			this->addtab->Padding = System::Windows::Forms::Padding(3);
			this->addtab->Size = System::Drawing::Size(644, 174);
			this->addtab->TabIndex = 0;
			this->addtab->Text = L"Add";
			this->addtab->UseVisualStyleBackColor = true;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(24, 13);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(345, 15);
			this->label12->TabIndex = 30;
			this->label12->Text = L"Enter the information of the product you wish to add :";
			// 
			// productgrp
			// 
			this->productgrp->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->productgrp->Controls->Add(this->manufacturertxt);
			this->productgrp->Controls->Add(this->numStockAdd);
			this->productgrp->Controls->Add(this->nametxt);
			this->productgrp->Controls->Add(this->stocktxt);
			this->productgrp->Controls->Add(this->nameAdd);
			this->productgrp->Controls->Add(this->manufacturerAdd);
			this->productgrp->Controls->Add(this->categorytxt);
			this->productgrp->Controls->Add(this->categoryAdd);
			this->productgrp->Controls->Add(this->priceAdd);
			this->productgrp->Controls->Add(this->barcodetxt);
			this->productgrp->Controls->Add(this->pricetxt);
			this->productgrp->Controls->Add(this->barcodeAdd);
			this->productgrp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->productgrp->Location = System::Drawing::Point(16, 36);
			this->productgrp->Name = L"productgrp";
			this->productgrp->Size = System::Drawing::Size(600, 131);
			this->productgrp->TabIndex = 0;
			this->productgrp->TabStop = false;
			this->productgrp->Text = L"Product";
			// 
			// manufacturertxt
			// 
			this->manufacturertxt->AutoSize = true;
			this->manufacturertxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->manufacturertxt->Location = System::Drawing::Point(327, 26);
			this->manufacturertxt->Name = L"manufacturertxt";
			this->manufacturertxt->Size = System::Drawing::Size(70, 13);
			this->manufacturertxt->TabIndex = 26;
			this->manufacturertxt->Text = L"Manufacturer";
			// 
			// numStockAdd
			// 
			this->numStockAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numStockAdd->Location = System::Drawing::Point(431, 91);
			this->numStockAdd->Name = L"numStockAdd";
			this->numStockAdd->Size = System::Drawing::Size(137, 20);
			this->numStockAdd->TabIndex = 5;
			this->numStockAdd->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// nametxt
			// 
			this->nametxt->AutoSize = true;
			this->nametxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->nametxt->Location = System::Drawing::Point(10, 29);
			this->nametxt->Name = L"nametxt";
			this->nametxt->Size = System::Drawing::Size(35, 13);
			this->nametxt->TabIndex = 18;
			this->nametxt->Text = L"Name";
			// 
			// stocktxt
			// 
			this->stocktxt->AutoSize = true;
			this->stocktxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->stocktxt->Location = System::Drawing::Point(327, 94);
			this->stocktxt->Name = L"stocktxt";
			this->stocktxt->Size = System::Drawing::Size(72, 13);
			this->stocktxt->TabIndex = 28;
			this->stocktxt->Text = L"Current Stock";
			// 
			// nameAdd
			// 
			this->nameAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->nameAdd->Location = System::Drawing::Point(90, 25);
			this->nameAdd->Name = L"nameAdd";
			this->nameAdd->Size = System::Drawing::Size(137, 20);
			this->nameAdd->TabIndex = 0;
			// 
			// manufacturerAdd
			// 
			this->manufacturerAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->manufacturerAdd->Location = System::Drawing::Point(431, 26);
			this->manufacturerAdd->Name = L"manufacturerAdd";
			this->manufacturerAdd->Size = System::Drawing::Size(137, 20);
			this->manufacturerAdd->TabIndex = 3;
			// 
			// categorytxt
			// 
			this->categorytxt->AutoSize = true;
			this->categorytxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->categorytxt->Location = System::Drawing::Point(10, 94);
			this->categorytxt->Name = L"categorytxt";
			this->categorytxt->Size = System::Drawing::Size(49, 13);
			this->categorytxt->TabIndex = 20;
			this->categorytxt->Text = L"Category";
			// 
			// categoryAdd
			// 
			this->categoryAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->categoryAdd->Location = System::Drawing::Point(90, 91);
			this->categoryAdd->Name = L"categoryAdd";
			this->categoryAdd->Size = System::Drawing::Size(137, 20);
			this->categoryAdd->TabIndex = 2;
			// 
			// priceAdd
			// 
			this->priceAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->priceAdd->Location = System::Drawing::Point(90, 58);
			this->priceAdd->Name = L"priceAdd";
			this->priceAdd->Size = System::Drawing::Size(137, 20);
			this->priceAdd->TabIndex = 1;
			this->priceAdd->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::priceAdd_KeyPress);
			// 
			// barcodetxt
			// 
			this->barcodetxt->AutoSize = true;
			this->barcodetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->barcodetxt->Location = System::Drawing::Point(327, 62);
			this->barcodetxt->Name = L"barcodetxt";
			this->barcodetxt->Size = System::Drawing::Size(47, 13);
			this->barcodetxt->TabIndex = 22;
			this->barcodetxt->Text = L"Barcode";
			// 
			// pricetxt
			// 
			this->pricetxt->AutoSize = true;
			this->pricetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->pricetxt->Location = System::Drawing::Point(10, 62);
			this->pricetxt->Name = L"pricetxt";
			this->pricetxt->Size = System::Drawing::Size(31, 13);
			this->pricetxt->TabIndex = 24;
			this->pricetxt->Text = L"Price";
			// 
			// barcodeAdd
			// 
			this->barcodeAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->barcodeAdd->Location = System::Drawing::Point(431, 59);
			this->barcodeAdd->Name = L"barcodeAdd";
			this->barcodeAdd->Size = System::Drawing::Size(137, 20);
			this->barcodeAdd->TabIndex = 4;
			this->barcodeAdd->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// deletetab
			// 
			this->deletetab->Controls->Add(this->deleteproducttxt);
			this->deletetab->Controls->Add(this->barcodeDelete);
			this->deletetab->Controls->Add(this->label13);
			this->deletetab->Location = System::Drawing::Point(4, 44);
			this->deletetab->Name = L"deletetab";
			this->deletetab->Padding = System::Windows::Forms::Padding(3);
			this->deletetab->Size = System::Drawing::Size(644, 174);
			this->deletetab->TabIndex = 1;
			this->deletetab->Text = L"Delete";
			this->deletetab->UseVisualStyleBackColor = true;
			// 
			// deleteproducttxt
			// 
			this->deleteproducttxt->AutoSize = true;
			this->deleteproducttxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->deleteproducttxt->Location = System::Drawing::Point(27, 22);
			this->deleteproducttxt->Name = L"deleteproducttxt";
			this->deleteproducttxt->Size = System::Drawing::Size(340, 15);
			this->deleteproducttxt->TabIndex = 31;
			this->deleteproducttxt->Text = L"Enter the barcode of the product you wish to delete :";
			// 
			// barcodeDelete
			// 
			this->barcodeDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->barcodeDelete->Location = System::Drawing::Point(96, 63);
			this->barcodeDelete->Name = L"barcodeDelete";
			this->barcodeDelete->Size = System::Drawing::Size(137, 20);
			this->barcodeDelete->TabIndex = 16;
			this->barcodeDelete->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label13->Location = System::Drawing::Point(27, 66);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(47, 13);
			this->label13->TabIndex = 16;
			this->label13->Text = L"Barcode";
			// 
			// restocktab
			// 
			this->restocktab->Controls->Add(this->label14);
			this->restocktab->Controls->Add(this->numAddRestock);
			this->restocktab->Controls->Add(this->restocktxt);
			this->restocktab->Controls->Add(this->barcodeRestock);
			this->restocktab->Controls->Add(this->restockbarcodetxt);
			this->restocktab->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restocktab->Location = System::Drawing::Point(4, 44);
			this->restocktab->Name = L"restocktab";
			this->restocktab->Padding = System::Windows::Forms::Padding(3);
			this->restocktab->Size = System::Drawing::Size(644, 174);
			this->restocktab->TabIndex = 2;
			this->restocktab->Text = L"Restock";
			this->restocktab->UseVisualStyleBackColor = true;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(27, 21);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(382, 15);
			this->label14->TabIndex = 22;
			this->label14->Text = L"Please enter the product barcode and its final stock value :";
			// 
			// numAddRestock
			// 
			this->numAddRestock->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->numAddRestock->Location = System::Drawing::Point(129, 102);
			this->numAddRestock->Name = L"numAddRestock";
			this->numAddRestock->Size = System::Drawing::Size(137, 26);
			this->numAddRestock->TabIndex = 20;
			this->numAddRestock->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// restocktxt
			// 
			this->restocktxt->AutoSize = true;
			this->restocktxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restocktxt->Location = System::Drawing::Point(27, 106);
			this->restocktxt->Name = L"restocktxt";
			this->restocktxt->Size = System::Drawing::Size(60, 13);
			this->restocktxt->TabIndex = 19;
			this->restocktxt->Text = L"Final Stock";
			// 
			// barcodeRestock
			// 
			this->barcodeRestock->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->barcodeRestock->Location = System::Drawing::Point(129, 62);
			this->barcodeRestock->Name = L"barcodeRestock";
			this->barcodeRestock->Size = System::Drawing::Size(137, 26);
			this->barcodeRestock->TabIndex = 18;
			this->barcodeRestock->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// restockbarcodetxt
			// 
			this->restockbarcodetxt->AutoSize = true;
			this->restockbarcodetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restockbarcodetxt->Location = System::Drawing::Point(27, 66);
			this->restockbarcodetxt->Name = L"restockbarcodetxt";
			this->restockbarcodetxt->Size = System::Drawing::Size(47, 13);
			this->restockbarcodetxt->TabIndex = 17;
			this->restockbarcodetxt->Text = L"Barcode";
			// 
			// disposetab
			// 
			this->disposetab->Controls->Add(this->disposetxt);
			this->disposetab->Controls->Add(this->barcodeDispose);
			this->disposetab->Controls->Add(this->disposebarcodetxt);
			this->disposetab->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->disposetab->Location = System::Drawing::Point(4, 44);
			this->disposetab->Name = L"disposetab";
			this->disposetab->Padding = System::Windows::Forms::Padding(3);
			this->disposetab->Size = System::Drawing::Size(644, 174);
			this->disposetab->TabIndex = 3;
			this->disposetab->Text = L"Dispose by barcode";
			this->disposetab->UseVisualStyleBackColor = true;
			// 
			// disposetxt
			// 
			this->disposetxt->AutoSize = true;
			this->disposetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->disposetxt->Location = System::Drawing::Point(27, 24);
			this->disposetxt->Name = L"disposetxt";
			this->disposetxt->Size = System::Drawing::Size(200, 15);
			this->disposetxt->TabIndex = 22;
			this->disposetxt->Text = L"Please enter product barcode:";
			// 
			// barcodeDispose
			// 
			this->barcodeDispose->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->barcodeDispose->Location = System::Drawing::Point(129, 59);
			this->barcodeDispose->Name = L"barcodeDispose";
			this->barcodeDispose->Size = System::Drawing::Size(137, 26);
			this->barcodeDispose->TabIndex = 19;
			this->barcodeDispose->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// disposebarcodetxt
			// 
			this->disposebarcodetxt->AutoSize = true;
			this->disposebarcodetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->disposebarcodetxt->Location = System::Drawing::Point(27, 66);
			this->disposebarcodetxt->Name = L"disposebarcodetxt";
			this->disposebarcodetxt->Size = System::Drawing::Size(47, 13);
			this->disposebarcodetxt->TabIndex = 18;
			this->disposebarcodetxt->Text = L"Barcode";
			// 
			// disposealltab
			// 
			this->disposealltab->Controls->Add(this->disposealltxt);
			this->disposealltab->Location = System::Drawing::Point(4, 44);
			this->disposealltab->Name = L"disposealltab";
			this->disposealltab->Padding = System::Windows::Forms::Padding(3);
			this->disposealltab->Size = System::Drawing::Size(644, 174);
			this->disposealltab->TabIndex = 4;
			this->disposealltab->Text = L"Dispose all expired";
			this->disposealltab->UseVisualStyleBackColor = true;
			// 
			// disposealltxt
			// 
			this->disposealltxt->AutoSize = true;
			this->disposealltxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->disposealltxt->Location = System::Drawing::Point(24, 23);
			this->disposealltxt->Name = L"disposealltxt";
			this->disposealltxt->Size = System::Drawing::Size(359, 15);
			this->disposealltxt->TabIndex = 24;
			this->disposealltxt->Text = L"To dispose all expired products, hit the Add Job button.";
			// 
			// saletab
			// 
			this->saletab->Controls->Add(this->saletxt);
			this->saletab->Controls->Add(this->numSoldSale);
			this->saletab->Controls->Add(this->salenumtxt);
			this->saletab->Controls->Add(this->barcodeSale);
			this->saletab->Controls->Add(this->salebarcodetxt);
			this->saletab->Location = System::Drawing::Point(4, 44);
			this->saletab->Name = L"saletab";
			this->saletab->Padding = System::Windows::Forms::Padding(3);
			this->saletab->Size = System::Drawing::Size(644, 174);
			this->saletab->TabIndex = 5;
			this->saletab->Text = L"Sales";
			this->saletab->UseVisualStyleBackColor = true;
			// 
			// saletxt
			// 
			this->saletxt->AutoSize = true;
			this->saletxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->saletxt->Location = System::Drawing::Point(24, 23);
			this->saletxt->Name = L"saletxt";
			this->saletxt->Size = System::Drawing::Size(364, 15);
			this->saletxt->TabIndex = 25;
			this->saletxt->Text = L"Please enter the product barcode and the number sold :";
			// 
			// numSoldSale
			// 
			this->numSoldSale->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numSoldSale->Location = System::Drawing::Point(129, 102);
			this->numSoldSale->Name = L"numSoldSale";
			this->numSoldSale->Size = System::Drawing::Size(137, 20);
			this->numSoldSale->TabIndex = 24;
			this->numSoldSale->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// salenumtxt
			// 
			this->salenumtxt->AutoSize = true;
			this->salenumtxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->salenumtxt->Location = System::Drawing::Point(27, 106);
			this->salenumtxt->Name = L"salenumtxt";
			this->salenumtxt->Size = System::Drawing::Size(68, 13);
			this->salenumtxt->TabIndex = 23;
			this->salenumtxt->Text = L"Number Sold";
			// 
			// barcodeSale
			// 
			this->barcodeSale->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->barcodeSale->Location = System::Drawing::Point(129, 62);
			this->barcodeSale->Name = L"barcodeSale";
			this->barcodeSale->Size = System::Drawing::Size(137, 20);
			this->barcodeSale->TabIndex = 22;
			this->barcodeSale->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// salebarcodetxt
			// 
			this->salebarcodetxt->AutoSize = true;
			this->salebarcodetxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->salebarcodetxt->Location = System::Drawing::Point(27, 66);
			this->salebarcodetxt->Name = L"salebarcodetxt";
			this->salebarcodetxt->Size = System::Drawing::Size(47, 13);
			this->salebarcodetxt->TabIndex = 21;
			this->salebarcodetxt->Text = L"Barcode";
			// 
			// discounttab
			// 
			this->discounttab->Controls->Add(this->changediscounttxt);
			this->discounttab->Controls->Add(this->discountDiscount);
			this->discounttab->Controls->Add(this->discounttxt);
			this->discounttab->Controls->Add(this->daysLeftDiscount);
			this->discounttab->Controls->Add(this->dayslefttxt);
			this->discounttab->Location = System::Drawing::Point(4, 44);
			this->discounttab->Name = L"discounttab";
			this->discounttab->Padding = System::Windows::Forms::Padding(3);
			this->discounttab->Size = System::Drawing::Size(644, 174);
			this->discounttab->TabIndex = 6;
			this->discounttab->Text = L"Set discount by expiry";
			this->discounttab->UseVisualStyleBackColor = true;
			// 
			// changediscounttxt
			// 
			this->changediscounttxt->AutoSize = true;
			this->changediscounttxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->changediscounttxt->Location = System::Drawing::Point(24, 23);
			this->changediscounttxt->Name = L"changediscounttxt";
			this->changediscounttxt->Size = System::Drawing::Size(373, 15);
			this->changediscounttxt->TabIndex = 25;
			this->changediscounttxt->Text = L"Please enter the new discount rate for expiring products :";
			// 
			// discountDiscount
			// 
			this->discountDiscount->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->discountDiscount->Location = System::Drawing::Point(113, 99);
			this->discountDiscount->Name = L"discountDiscount";
			this->discountDiscount->Size = System::Drawing::Size(137, 26);
			this->discountDiscount->TabIndex = 24;
			this->discountDiscount->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::priceAdd_KeyPress);
			// 
			// discounttxt
			// 
			this->discounttxt->AutoSize = true;
			this->discounttxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->discounttxt->Location = System::Drawing::Point(27, 106);
			this->discounttxt->Name = L"discounttxt";
			this->discounttxt->Size = System::Drawing::Size(49, 13);
			this->discounttxt->TabIndex = 23;
			this->discounttxt->Text = L"Discount";
			// 
			// daysLeftDiscount
			// 
			this->daysLeftDiscount->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->daysLeftDiscount->Location = System::Drawing::Point(113, 59);
			this->daysLeftDiscount->Name = L"daysLeftDiscount";
			this->daysLeftDiscount->Size = System::Drawing::Size(137, 26);
			this->daysLeftDiscount->TabIndex = 22;
			this->daysLeftDiscount->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// dayslefttxt
			// 
			this->dayslefttxt->AutoSize = true;
			this->dayslefttxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->dayslefttxt->Location = System::Drawing::Point(27, 66);
			this->dayslefttxt->Name = L"dayslefttxt";
			this->dayslefttxt->Size = System::Drawing::Size(52, 13);
			this->dayslefttxt->TabIndex = 21;
			this->dayslefttxt->Text = L"Days Left";
			// 
			// restockMtab
			// 
			this->restockMtab->Controls->Add(this->restockMtxt);
			this->restockMtab->Controls->Add(this->numAddRestockManufacturer);
			this->restockMtab->Controls->Add(this->restockMstocktxt);
			this->restockMtab->Controls->Add(this->restockMmanutxt);
			this->restockMtab->Controls->Add(this->manufacturerRestockManufacturer);
			this->restockMtab->Location = System::Drawing::Point(4, 44);
			this->restockMtab->Name = L"restockMtab";
			this->restockMtab->Padding = System::Windows::Forms::Padding(3);
			this->restockMtab->Size = System::Drawing::Size(644, 174);
			this->restockMtab->TabIndex = 7;
			this->restockMtab->Text = L"Restock by manufacturer";
			this->restockMtab->UseVisualStyleBackColor = true;
			// 
			// restockMtxt
			// 
			this->restockMtxt->AutoSize = true;
			this->restockMtxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->restockMtxt->Location = System::Drawing::Point(24, 23);
			this->restockMtxt->Name = L"restockMtxt";
			this->restockMtxt->Size = System::Drawing::Size(426, 15);
			this->restockMtxt->TabIndex = 25;
			this->restockMtxt->Text = L"Please enter the manufacturer and its products\' final stock value :";
			// 
			// numAddRestockManufacturer
			// 
			this->numAddRestockManufacturer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numAddRestockManufacturer->Location = System::Drawing::Point(129, 102);
			this->numAddRestockManufacturer->Name = L"numAddRestockManufacturer";
			this->numAddRestockManufacturer->Size = System::Drawing::Size(137, 20);
			this->numAddRestockManufacturer->TabIndex = 1;
			this->numAddRestockManufacturer->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// restockMstocktxt
			// 
			this->restockMstocktxt->AutoSize = true;
			this->restockMstocktxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restockMstocktxt->Location = System::Drawing::Point(27, 106);
			this->restockMstocktxt->Name = L"restockMstocktxt";
			this->restockMstocktxt->Size = System::Drawing::Size(60, 13);
			this->restockMstocktxt->TabIndex = 21;
			this->restockMstocktxt->Text = L"Final Stock";
			// 
			// restockMmanutxt
			// 
			this->restockMmanutxt->AutoSize = true;
			this->restockMmanutxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restockMmanutxt->Location = System::Drawing::Point(27, 66);
			this->restockMmanutxt->Name = L"restockMmanutxt";
			this->restockMmanutxt->Size = System::Drawing::Size(70, 13);
			this->restockMmanutxt->TabIndex = 23;
			this->restockMmanutxt->Text = L"Manufacturer";
			// 
			// manufacturerRestockManufacturer
			// 
			this->manufacturerRestockManufacturer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->manufacturerRestockManufacturer->Location = System::Drawing::Point(129, 62);
			this->manufacturerRestockManufacturer->Name = L"manufacturerRestockManufacturer";
			this->manufacturerRestockManufacturer->Size = System::Drawing::Size(137, 20);
			this->manufacturerRestockManufacturer->TabIndex = 0;
			// 
			// restockCtab
			// 
			this->restockCtab->Controls->Add(this->label15);
			this->restockCtab->Controls->Add(this->categoryRestockCategory);
			this->restockCtab->Controls->Add(this->label26);
			this->restockCtab->Controls->Add(this->numAddRestockCategory);
			this->restockCtab->Controls->Add(this->label27);
			this->restockCtab->Location = System::Drawing::Point(4, 44);
			this->restockCtab->Name = L"restockCtab";
			this->restockCtab->Padding = System::Windows::Forms::Padding(3);
			this->restockCtab->Size = System::Drawing::Size(644, 174);
			this->restockCtab->TabIndex = 8;
			this->restockCtab->Text = L"Restock by category";
			this->restockCtab->UseVisualStyleBackColor = true;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(24, 23);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(424, 15);
			this->label15->TabIndex = 29;
			this->label15->Text = L"Please enter the product category and final products stock value :";
			// 
			// categoryRestockCategory
			// 
			this->categoryRestockCategory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->categoryRestockCategory->Location = System::Drawing::Point(129, 62);
			this->categoryRestockCategory->Name = L"categoryRestockCategory";
			this->categoryRestockCategory->Size = System::Drawing::Size(137, 20);
			this->categoryRestockCategory->TabIndex = 0;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label26->Location = System::Drawing::Point(27, 66);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(49, 13);
			this->label26->TabIndex = 27;
			this->label26->Text = L"Category";
			// 
			// numAddRestockCategory
			// 
			this->numAddRestockCategory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numAddRestockCategory->Location = System::Drawing::Point(129, 102);
			this->numAddRestockCategory->Name = L"numAddRestockCategory";
			this->numAddRestockCategory->Size = System::Drawing::Size(137, 20);
			this->numAddRestockCategory->TabIndex = 1;
			this->numAddRestockCategory->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label27->Location = System::Drawing::Point(27, 106);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(60, 13);
			this->label27->TabIndex = 25;
			this->label27->Text = L"Final Stock";
			// 
			// tabPage11
			// 
			this->tabPage11->Controls->Add(this->restockLtxt);
			this->tabPage11->Controls->Add(this->numAddRestockLeft);
			this->tabPage11->Controls->Add(this->restockLfinalstocktxt);
			this->tabPage11->Controls->Add(this->leftRestockLeft);
			this->tabPage11->Controls->Add(this->restockLcurrstocktxt);
			this->tabPage11->Location = System::Drawing::Point(4, 44);
			this->tabPage11->Name = L"tabPage11";
			this->tabPage11->Padding = System::Windows::Forms::Padding(3);
			this->tabPage11->Size = System::Drawing::Size(644, 174);
			this->tabPage11->TabIndex = 9;
			this->tabPage11->Text = L"Restock based on current stock";
			this->tabPage11->UseVisualStyleBackColor = true;
			// 
			// restockLtxt
			// 
			this->restockLtxt->AutoSize = true;
			this->restockLtxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->restockLtxt->Location = System::Drawing::Point(24, 23);
			this->restockLtxt->Name = L"restockLtxt";
			this->restockLtxt->Size = System::Drawing::Size(349, 15);
			this->restockLtxt->TabIndex = 29;
			this->restockLtxt->Text = L"Restock all products with fewer than min stock value :";
			// 
			// numAddRestockLeft
			// 
			this->numAddRestockLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numAddRestockLeft->Location = System::Drawing::Point(129, 102);
			this->numAddRestockLeft->Name = L"numAddRestockLeft";
			this->numAddRestockLeft->Size = System::Drawing::Size(137, 20);
			this->numAddRestockLeft->TabIndex = 28;
			this->numAddRestockLeft->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// restockLfinalstocktxt
			// 
			this->restockLfinalstocktxt->AutoSize = true;
			this->restockLfinalstocktxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restockLfinalstocktxt->Location = System::Drawing::Point(27, 106);
			this->restockLfinalstocktxt->Name = L"restockLfinalstocktxt";
			this->restockLfinalstocktxt->Size = System::Drawing::Size(60, 13);
			this->restockLfinalstocktxt->TabIndex = 27;
			this->restockLfinalstocktxt->Text = L"Final Stock";
			// 
			// leftRestockLeft
			// 
			this->leftRestockLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->leftRestockLeft->Location = System::Drawing::Point(129, 62);
			this->leftRestockLeft->Name = L"leftRestockLeft";
			this->leftRestockLeft->Size = System::Drawing::Size(137, 20);
			this->leftRestockLeft->TabIndex = 26;
			this->leftRestockLeft->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::num_KeyPress);
			// 
			// restockLcurrstocktxt
			// 
			this->restockLcurrstocktxt->AutoSize = true;
			this->restockLcurrstocktxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->restockLcurrstocktxt->Location = System::Drawing::Point(27, 66);
			this->restockLcurrstocktxt->Name = L"restockLcurrstocktxt";
			this->restockLcurrstocktxt->Size = System::Drawing::Size(55, 13);
			this->restockLcurrstocktxt->TabIndex = 25;
			this->restockLcurrstocktxt->Text = L"Min Stock";
			// 
			// numjobsaddedtxt
			// 
			this->numjobsaddedtxt->AutoSize = true;
			this->numjobsaddedtxt->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->numjobsaddedtxt->Location = System::Drawing::Point(686, 77);
			this->numjobsaddedtxt->Name = L"numjobsaddedtxt";
			this->numjobsaddedtxt->Size = System::Drawing::Size(63, 26);
			this->numjobsaddedtxt->TabIndex = 34;
			this->numjobsaddedtxt->Text = L"Number Of\r\nJobs Added";
			// 
			// finishbtn
			// 
			this->finishbtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->finishbtn->Location = System::Drawing::Point(680, 208);
			this->finishbtn->Name = L"finishbtn";
			this->finishbtn->Size = System::Drawing::Size(78, 64);
			this->finishbtn->TabIndex = 2;
			this->finishbtn->Text = L"Finish";
			this->finishbtn->UseVisualStyleBackColor = true;
			this->finishbtn->Click += gcnew System::EventHandler(this, &ManagerUI::finishbtn_Click);
			// 
			// numjobsaddedbox
			// 
			this->numjobsaddedbox->Location = System::Drawing::Point(680, 117);
			this->numjobsaddedbox->Name = L"numjobsaddedbox";
			this->numjobsaddedbox->ReadOnly = true;
			this->numjobsaddedbox->Size = System::Drawing::Size(78, 20);
			this->numjobsaddedbox->TabIndex = 33;
			this->numjobsaddedbox->Text = L"0";
			// 
			// tabPageUserAcc
			// 
			this->tabPageUserAcc->Controls->Add(this->databasegrp);
			this->tabPageUserAcc->Controls->Add(this->addgrp);
			this->tabPageUserAcc->Controls->Add(this->searchaccgrp);
			this->tabPageUserAcc->Controls->Add(this->accountsgrp);
			this->tabPageUserAcc->Location = System::Drawing::Point(4, 22);
			this->tabPageUserAcc->Name = L"tabPageUserAcc";
			this->tabPageUserAcc->Size = System::Drawing::Size(776, 370);
			this->tabPageUserAcc->TabIndex = 3;
			this->tabPageUserAcc->Text = L"User Accounts";
			this->tabPageUserAcc->UseVisualStyleBackColor = true;
			// 
			// databasegrp
			// 
			this->databasegrp->Controls->Add(this->savedbbtn);
			this->databasegrp->Controls->Add(this->cleardbbtn);
			this->databasegrp->Location = System::Drawing::Point(9, 252);
			this->databasegrp->Name = L"databasegrp";
			this->databasegrp->Size = System::Drawing::Size(430, 115);
			this->databasegrp->TabIndex = 8;
			this->databasegrp->TabStop = false;
			this->databasegrp->Text = L"Accounts Database";
			// 
			// savedbbtn
			// 
			this->savedbbtn->Location = System::Drawing::Point(231, 44);
			this->savedbbtn->Name = L"savedbbtn";
			this->savedbbtn->Size = System::Drawing::Size(169, 45);
			this->savedbbtn->TabIndex = 1;
			this->savedbbtn->Text = L"Save Database";
			this->savedbbtn->UseVisualStyleBackColor = true;
			this->savedbbtn->Click += gcnew System::EventHandler(this, &ManagerUI::saveddbbtn_Click);
			// 
			// cleardbbtn
			// 
			this->cleardbbtn->Location = System::Drawing::Point(25, 44);
			this->cleardbbtn->Name = L"cleardbbtn";
			this->cleardbbtn->Size = System::Drawing::Size(175, 45);
			this->cleardbbtn->TabIndex = 0;
			this->cleardbbtn->Text = L"Reset Changes";
			this->cleardbbtn->UseVisualStyleBackColor = true;
			this->cleardbbtn->Click += gcnew System::EventHandler(this, &ManagerUI::cleardbbtn_Click);
			// 
			// addgrp
			// 
			this->addgrp->Controls->Add(this->label10);
			this->addgrp->Controls->Add(this->addaccountbtn);
			this->addgrp->Controls->Add(this->radiobtnManager);
			this->addgrp->Controls->Add(this->radiobtnCashier);
			this->addgrp->Controls->Add(this->label9);
			this->addgrp->Controls->Add(this->label8);
			this->addgrp->Controls->Add(this->passwordbox);
			this->addgrp->Controls->Add(this->userIDbox);
			this->addgrp->Location = System::Drawing::Point(9, 85);
			this->addgrp->Name = L"addgrp";
			this->addgrp->Size = System::Drawing::Size(430, 162);
			this->addgrp->TabIndex = 7;
			this->addgrp->TabStop = false;
			this->addgrp->Text = L"Add New Account";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(22, 128);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(71, 13);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Access Level";
			// 
			// addaccountbtn
			// 
			this->addaccountbtn->Location = System::Drawing::Point(325, 38);
			this->addaccountbtn->Name = L"addaccountbtn";
			this->addaccountbtn->Size = System::Drawing::Size(75, 105);
			this->addaccountbtn->TabIndex = 5;
			this->addaccountbtn->Text = L"Add account";
			this->addaccountbtn->UseVisualStyleBackColor = true;
			this->addaccountbtn->Click += gcnew System::EventHandler(this, &ManagerUI::addaccountbtn_Click);
			// 
			// radiobtnManager
			// 
			this->radiobtnManager->AutoCheck = false;
			this->radiobtnManager->AutoSize = true;
			this->radiobtnManager->Location = System::Drawing::Point(240, 126);
			this->radiobtnManager->Name = L"radiobtnManager";
			this->radiobtnManager->Size = System::Drawing::Size(67, 17);
			this->radiobtnManager->TabIndex = 4;
			this->radiobtnManager->TabStop = true;
			this->radiobtnManager->Text = L"Manager";
			this->radiobtnManager->UseVisualStyleBackColor = true;
			this->radiobtnManager->Click += gcnew System::EventHandler(this, &ManagerUI::radiobtnManager_Click);
			// 
			// radiobtnCashier
			// 
			this->radiobtnCashier->AutoCheck = false;
			this->radiobtnCashier->AutoSize = true;
			this->radiobtnCashier->Checked = true;
			this->radiobtnCashier->Location = System::Drawing::Point(112, 126);
			this->radiobtnCashier->Name = L"radiobtnCashier";
			this->radiobtnCashier->Size = System::Drawing::Size(60, 17);
			this->radiobtnCashier->TabIndex = 3;
			this->radiobtnCashier->TabStop = true;
			this->radiobtnCashier->Text = L"Cashier";
			this->radiobtnCashier->UseVisualStyleBackColor = true;
			this->radiobtnCashier->Click += gcnew System::EventHandler(this, &ManagerUI::radiobtnCashier_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(22, 85);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(53, 13);
			this->label9->TabIndex = 14;
			this->label9->Text = L"Password";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(22, 43);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(40, 13);
			this->label8->TabIndex = 13;
			this->label8->Text = L"UserID";
			// 
			// passwordbox
			// 
			this->passwordbox->Location = System::Drawing::Point(112, 82);
			this->passwordbox->Name = L"passwordbox";
			this->passwordbox->Size = System::Drawing::Size(195, 20);
			this->passwordbox->TabIndex = 2;
			this->passwordbox->UseSystemPasswordChar = true;
			this->passwordbox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->passwordbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::passwordbox_KeyPress);
			// 
			// userIDbox
			// 
			this->userIDbox->Location = System::Drawing::Point(112, 40);
			this->userIDbox->Name = L"userIDbox";
			this->userIDbox->Size = System::Drawing::Size(195, 20);
			this->userIDbox->TabIndex = 1;
			this->userIDbox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->userIDbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::userIDbox_KeyPress);
			// 
			// searchaccgrp
			// 
			this->searchaccgrp->Controls->Add(this->searchidbtn);
			this->searchaccgrp->Controls->Add(this->searchIDbox);
			this->searchaccgrp->Controls->Add(this->button1);
			this->searchaccgrp->Controls->Add(this->label5);
			this->searchaccgrp->Location = System::Drawing::Point(8, 3);
			this->searchaccgrp->Name = L"searchaccgrp";
			this->searchaccgrp->Size = System::Drawing::Size(431, 76);
			this->searchaccgrp->TabIndex = 6;
			this->searchaccgrp->TabStop = false;
			this->searchaccgrp->Text = L"Search Existing Accounts";
			// 
			// searchidbtn
			// 
			this->searchidbtn->Location = System::Drawing::Point(326, 30);
			this->searchidbtn->Name = L"searchidbtn";
			this->searchidbtn->Size = System::Drawing::Size(75, 23);
			this->searchidbtn->TabIndex = 1;
			this->searchidbtn->Text = L"Search";
			this->searchidbtn->UseVisualStyleBackColor = true;
			this->searchidbtn->Click += gcnew System::EventHandler(this, &ManagerUI::searchidbtn_Click);
			// 
			// searchIDbox
			// 
			this->searchIDbox->Location = System::Drawing::Point(113, 32);
			this->searchIDbox->Name = L"searchIDbox";
			this->searchIDbox->Size = System::Drawing::Size(195, 20);
			this->searchIDbox->TabIndex = 0;
			this->searchIDbox->Enter += gcnew System::EventHandler(this, &ManagerUI::selectAll);
			this->searchIDbox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ManagerUI::searchIDbox_KeyPress);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(564, 32);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(61, 48);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Search";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(23, 35);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(77, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Search UserID";
			// 
			// accountsgrp
			// 
			this->accountsgrp->Controls->Add(this->resultsListViewAcc);
			this->accountsgrp->Location = System::Drawing::Point(445, 3);
			this->accountsgrp->Name = L"accountsgrp";
			this->accountsgrp->Size = System::Drawing::Size(324, 364);
			this->accountsgrp->TabIndex = 9;
			this->accountsgrp->TabStop = false;
			this->accountsgrp->Text = L"Accounts";
			// 
			// resultsListViewAcc
			// 
			this->resultsListViewAcc->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->resultsListViewAcc->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->accessCol, 
				this->userIDCol});
			this->resultsListViewAcc->ContextMenuStrip = this->accountsContextMenu;
			this->resultsListViewAcc->FullRowSelect = true;
			this->resultsListViewAcc->Location = System::Drawing::Point(6, 21);
			this->resultsListViewAcc->Name = L"resultsListViewAcc";
			this->resultsListViewAcc->Size = System::Drawing::Size(312, 328);
			this->resultsListViewAcc->TabIndex = 5;
			this->resultsListViewAcc->TileSize = System::Drawing::Size(168, 15);
			this->resultsListViewAcc->UseCompatibleStateImageBehavior = false;
			this->resultsListViewAcc->View = System::Windows::Forms::View::Details;
			this->resultsListViewAcc->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &ManagerUI::resultsListViewAcc_ColumnClick);
			// 
			// accessCol
			// 
			this->accessCol->Text = L"Access Level";
			this->accessCol->Width = 78;
			// 
			// userIDCol
			// 
			this->userIDCol->Text = L"User ID";
			this->userIDCol->Width = 221;
			// 
			// accountsContextMenu
			// 
			this->accountsContextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->deleteAccountToolStripMenuItem});
			this->accountsContextMenu->Name = L"accountsContextMenu";
			this->accountsContextMenu->Size = System::Drawing::Size(156, 26);
			// 
			// deleteAccountToolStripMenuItem
			// 
			this->deleteAccountToolStripMenuItem->Name = L"deleteAccountToolStripMenuItem";
			this->deleteAccountToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->deleteAccountToolStripMenuItem->Text = L"Delete Account";
			this->deleteAccountToolStripMenuItem->Click += gcnew System::EventHandler(this, &ManagerUI::deleteAccountToolStripMenuItem_Click);
			// 
			// backgroundWorkerFillResults
			// 
			this->backgroundWorkerFillResults->WorkerReportsProgress = true;
			this->backgroundWorkerFillResults->WorkerSupportsCancellation = true;
			this->backgroundWorkerFillResults->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ManagerUI::backgroundWorkerFillResults_DoWork);
			this->backgroundWorkerFillResults->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ManagerUI::backgroundWorkerFillResults_RunWorkerCompleted);
			// 
			// ManagerUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 442);
			this->Controls->Add(this->tabControl);
			this->Name = L"ManagerUI";
			this->Text = L"CEG ICMS - Manager";
			this->Load += gcnew System::EventHandler(this, &ManagerUI::ManagerUI_Load);
			this->Controls->SetChildIndex(this->tabControl, 0);
			this->Controls->SetChildIndex(this->backgroundWorkerCancelBtn, 0);
			this->tabControl->ResumeLayout(false);
			this->tabPageModInv->ResumeLayout(false);
			this->resultgrpInv->ResumeLayout(false);
			this->resultContextMenu->ResumeLayout(false);
			this->searchgrpInv->ResumeLayout(false);
			this->searchgrpInv->PerformLayout();
			this->tabPageTopPrd->ResumeLayout(false);
			this->resultgrpPrd->ResumeLayout(false);
			this->searchgrpPrd->ResumeLayout(false);
			this->searchgrpPrd->PerformLayout();
			this->tabPageTopManu->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->searchgrpManu->ResumeLayout(false);
			this->searchgrpManu->PerformLayout();
			this->tabPageBatchJob->ResumeLayout(false);
			this->tabPageBatchJob->PerformLayout();
			this->addbatchjobgrp->ResumeLayout(false);
			this->tabcontrol1->ResumeLayout(false);
			this->addtab->ResumeLayout(false);
			this->addtab->PerformLayout();
			this->productgrp->ResumeLayout(false);
			this->productgrp->PerformLayout();
			this->deletetab->ResumeLayout(false);
			this->deletetab->PerformLayout();
			this->restocktab->ResumeLayout(false);
			this->restocktab->PerformLayout();
			this->disposetab->ResumeLayout(false);
			this->disposetab->PerformLayout();
			this->disposealltab->ResumeLayout(false);
			this->disposealltab->PerformLayout();
			this->saletab->ResumeLayout(false);
			this->saletab->PerformLayout();
			this->discounttab->ResumeLayout(false);
			this->discounttab->PerformLayout();
			this->restockMtab->ResumeLayout(false);
			this->restockMtab->PerformLayout();
			this->restockCtab->ResumeLayout(false);
			this->restockCtab->PerformLayout();
			this->tabPage11->ResumeLayout(false);
			this->tabPage11->PerformLayout();
			this->tabPageUserAcc->ResumeLayout(false);
			this->databasegrp->ResumeLayout(false);
			this->addgrp->ResumeLayout(false);
			this->addgrp->PerformLayout();
			this->searchaccgrp->ResumeLayout(false);
			this->searchaccgrp->PerformLayout();
			this->accountsgrp->ResumeLayout(false);
			this->accountsContextMenu->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		/******** UI FUNCTIONS ********/
	private:
		void ManagerUI_Load(System::Object^  sender, System::EventArgs^  e);
		void tabControl_Enter(System::Object^  sender, System::EventArgs^  e);
		void tabControl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		void selectAll(System::Object^  sender, System::EventArgs^  e);
		void selectDefault();
		void num_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
	protected:
		virtual void switchUIViews() override;

		/******** "SEARCH PRODUCTS" TAB ********/
	private:
		void searchBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void searchType_TextClick(System::Object^  sender, System::EventArgs^  e);
		void searchBtn_Click(System::Object^  sender, System::EventArgs^  e);
		void resultsListViewInv_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);

		/******** "TOP PRODUCTS" TAB ********/
		void numTopBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void filterBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void catFilterBtn_Click(System::Object^  sender, System::EventArgs^  e);
		void manuFilterBtn_Click(System::Object^  sender, System::EventArgs^  e);
		void searchPrdBtn_Click(System::Object^  sender, System::EventArgs^  e);
		void resultsListViewPrd_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);

		/******** "TOP MANUFACTURERS" TAB ********/
		void numTopManuBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void manuFilterBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void manuCheckBox_CheckStateChanged(System::Object^  sender, System::EventArgs^  e);
		void searchManuBtn_Click(System::Object^  sender, System::EventArgs^  e);
		void ManagerUI::resultsListViewManu_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);

		/******** "USER ACCOUNTS" TAB  ********/
		void resultsListViewAcc_Load();
		void addaccountbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void deleteAccountToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void saveddbbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void cleardbbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void radiobtnCashier_Click(System::Object^  sender, System::EventArgs^  e) ;
		void radiobtnManager_Click(System::Object^  sender, System::EventArgs^  e);
		void userIDbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void passwordbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void searchIDbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		void searchidbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void resultsListViewAcc_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);

		/******** "BATCH JOBS" TAB  ********/
		void addbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void finishbtn_Click(System::Object^  sender, System::EventArgs^  e);
		void priceAdd_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

		/******** RESULTS WINDOW FUNCTIONS ********/
		void updateResults(ListView^ resultWindow);
		void backgroundWorkerFillResults_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
		void backgroundWorkerFillResults_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e);
		void ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e);
	protected:
		virtual void backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) override;

		/******** INVENTORY CONTROL CALLER FUNCTIONS  ********/
	private:
		void resultContextMenu_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
		void resultsListViewInv_DoubleClick(System::Object^  sender, System::EventArgs^  e);
		void perishableToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void nonPerishableToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void editProductToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void deleteProductToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

	};
}
