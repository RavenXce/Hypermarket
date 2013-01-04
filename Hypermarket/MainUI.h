#pragma once
#include "wrapper.h"
#include "date.h"
#include "inventory.h"
#include "password.h"

namespace Hypermarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainUI
	/// </summary>
	public ref class MainUI : public System::Windows::Forms::Form
	{
	protected:	
		int* _next;
		string* _curUser;
		Inventory *inv;
		Password *accounts;
		System::ComponentModel::Container ^components;	

#pragma region Windows Form Automated Declaration Region
	protected: 
		System::Windows::Forms::Button^  backgroundWorkerCancelBtn;
		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  changeUserToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  inventoryToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  loadInventoryToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  saveInventoryToolStripMenuItem;
		System::Windows::Forms::OpenFileDialog^  openFileDialog1;
		System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
		System::Windows::Forms::StatusStrip^  statusStrip1;
		System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
		System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
		System::Windows::Forms::ToolStripMenuItem^  switchUIViewsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  batchJobsToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  selectBatchFileToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^  executeBatchJobsToolStripMenuItem;	
#pragma endregion
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->backgroundWorkerCancelBtn = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->switchUIViewsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changeUserToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->inventoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadInventoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveInventoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->batchJobsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectBatchFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->executeBatchJobsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// backgroundWorkerCancelBtn
			// 
			this->backgroundWorkerCancelBtn->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->backgroundWorkerCancelBtn->Enabled = false;
			this->backgroundWorkerCancelBtn->Location = System::Drawing::Point(743, 423);
			this->backgroundWorkerCancelBtn->Name = L"backgroundWorkerCancelBtn";
			this->backgroundWorkerCancelBtn->Size = System::Drawing::Size(0, 0);
			this->backgroundWorkerCancelBtn->TabIndex = 29;
			this->backgroundWorkerCancelBtn->UseVisualStyleBackColor = true;
			this->backgroundWorkerCancelBtn->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainUI::backgroundWorkerCancelBtn_KeyPress);
			this->backgroundWorkerCancelBtn->Leave += gcnew System::EventHandler(this, &MainUI::backgroundWorkerCancelBtn_Leave);
			this->backgroundWorkerCancelBtn->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainUI::backgroundWorkerCancelBtn_PreviewKeyDown);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->inventoryToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(784, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->switchUIViewsToolStripMenuItem, 
				this->changeUserToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// switchUIViewsToolStripMenuItem
			// 
			this->switchUIViewsToolStripMenuItem->Name = L"switchUIViewsToolStripMenuItem";
			this->switchUIViewsToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->switchUIViewsToolStripMenuItem->Text = L"Switch View";
			this->switchUIViewsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::switchUIViewsToolStripMenuItem_Click);
			// 
			// changeUserToolStripMenuItem
			// 
			this->changeUserToolStripMenuItem->Name = L"changeUserToolStripMenuItem";
			this->changeUserToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->changeUserToolStripMenuItem->Text = L"Change User";
			this->changeUserToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::changeUserToolStripMenuItem_Click);
			// 
			// inventoryToolStripMenuItem
			// 
			this->inventoryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->loadInventoryToolStripMenuItem, 
				this->saveInventoryToolStripMenuItem, this->batchJobsToolStripMenuItem});
			this->inventoryToolStripMenuItem->Name = L"inventoryToolStripMenuItem";
			this->inventoryToolStripMenuItem->Size = System::Drawing::Size(69, 20);
			this->inventoryToolStripMenuItem->Text = L"Inventory";
			// 
			// loadInventoryToolStripMenuItem
			// 
			this->loadInventoryToolStripMenuItem->Name = L"loadInventoryToolStripMenuItem";
			this->loadInventoryToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->loadInventoryToolStripMenuItem->Text = L"Load Inventory";
			this->loadInventoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::loadInventoryToolStripMenuItem_Click);
			// 
			// saveInventoryToolStripMenuItem
			// 
			this->saveInventoryToolStripMenuItem->Name = L"saveInventoryToolStripMenuItem";
			this->saveInventoryToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->saveInventoryToolStripMenuItem->Text = L"Save Inventory";
			this->saveInventoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::saveInventoryToolStripMenuItem_Click);
			// 
			// batchJobsToolStripMenuItem
			// 
			this->batchJobsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->selectBatchFileToolStripMenuItem, 
				this->executeBatchJobsToolStripMenuItem});
			this->batchJobsToolStripMenuItem->Name = L"batchJobsToolStripMenuItem";
			this->batchJobsToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->batchJobsToolStripMenuItem->Text = L"Batch Jobs";
			// 
			// selectBatchFileToolStripMenuItem
			// 
			this->selectBatchFileToolStripMenuItem->Name = L"selectBatchFileToolStripMenuItem";
			this->selectBatchFileToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->selectBatchFileToolStripMenuItem->Text = L"Select Batch File...";
			this->selectBatchFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::selectBatchFileToolStripMenuItem_Click);
			// 
			// executeBatchJobsToolStripMenuItem
			// 
			this->executeBatchJobsToolStripMenuItem->Name = L"executeBatchJobsToolStripMenuItem";
			this->executeBatchJobsToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->executeBatchJobsToolStripMenuItem->Text = L"Execute Batch Jobs";
			this->executeBatchJobsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainUI::executeBatchJobToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"txt";
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Text files|*.txt|All files|*.*";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"txt";
			this->saveFileDialog1->Filter = L"Text files|*.txt|All files|*.*";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripStatusLabel1, 
				this->toolStripProgressBar1});
			this->statusStrip1->Location = System::Drawing::Point(0, 420);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(784, 22);
			this->statusStrip1->TabIndex = 3;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			this->toolStripProgressBar1->Step = 1;
			this->toolStripProgressBar1->Visible = false;
			// 
			// MainUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 442);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->backgroundWorkerCancelBtn);
			this->Name = L"MainUI";
			this->Text = L"MainUI";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainUI::MainUI_FormClosing);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		MainUI();
		MainUI(int* next, string* curUser, Inventory* inv, Password* pwDB);
	protected:
		~MainUI();
		virtual void switchUIViews();
		void switchUIViewsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void changeUserToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);		
		void loadInventoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void saveInventoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void selectBatchFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void executeBatchJobToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		void backgroundWorkerCancelBtn_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e);
		void backgroundWorkerCancelBtn_Leave(System::Object^  sender, System::EventArgs^  e);
		virtual void backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);				
		void MainUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		void selectAllMain(System::Object^  sender, System::EventArgs^  e);
	};
}
