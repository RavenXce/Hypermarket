#include "stdafx.h"
#include "MainUI.h"

using namespace Hypermarket;

/* Initializers/Destructors */

MainUI::MainUI(){
	InitializeComponent();
}
MainUI::MainUI(int* next, string* curUser, Inventory* inv, Password* pwDB)
{
	_next = next;
	_curUser = curUser;
	accounts = pwDB;
	this->inv = inv;
	StartPosition = FormStartPosition::CenterScreen;
	InitializeComponent();
}
MainUI::~MainUI()
{
	if (components)
	{
		delete components;
	}
}

/* Toolstrip buttons */

void MainUI::switchUIViews(){}
void MainUI::switchUIViewsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	switchUIViews();
}
void MainUI::changeUserToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	*_next = 3;
	this->Close();
}
void MainUI::loadInventoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Title = "Load Inventory";		 
	openFileDialog1->FileName = "data.txt";
	if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		String^ filename = openFileDialog1->FileName;
		toolStripStatusLabel1->Text = "Loading Inventory...";
		toolStripStatusLabel1->ToolTipText = "Loading Inventory...";
		if(inv != NULL) inv->unloadInventory();
		if(!inv->loadInventory(Wrapper::toUnmanagedFileName(filename)))
			MessageBox::Show(
			"Failed to load file!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);					 
		toolStripStatusLabel1->Text = "Inventory loaded.";
	}
}
void MainUI::saveInventoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	saveFileDialog1->Title = "Save Inventory";		 
	saveFileDialog1->FileName = "data.txt";
	if(saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		String^ filename = saveFileDialog1->FileName;
		toolStripStatusLabel1->Text = "Saving Inventory...";
		toolStripStatusLabel1->ToolTipText = "Saving Inventory...";
		if(!inv->saveInventory(Wrapper::toUnmanagedFileName(filename)))
			MessageBox::Show(
			"Failed to save to file!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		toolStripStatusLabel1->Text = "Inventory saved.";
	}
}
void MainUI::selectBatchFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Title = "Load Batch";		 
	openFileDialog1->FileName = "batchjobs.txt";
	if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		String^ filename = openFileDialog1->FileName;
		toolStripStatusLabel1->Text = "Loading batch job file...";
		toolStripStatusLabel1->ToolTipText = "Loading batch job file...";
		if(inv != NULL) inv->unloadInventory();
		if(!inv->loadBatchfile(Wrapper::toUnmanagedFileName(filename))) //loads batch file
			MessageBox::Show(
			"Failed to load file!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);					 
		toolStripStatusLabel1->Text = "Batch jobs data loaded.";
	}
}
void MainUI::executeBatchJobToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->batchLoaded()){
		MessageBox::Show(
			"No batch jobs have been loaded or batch file is empty!", 
			"Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	if(!inv->isLoaded())
		if(MessageBox::Show(
			"No inventory has been loaded! Proceed with batch execution?", 
			"Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::No) return;
	MessageBox::Show(
		"Please select a location to save the log file for this operation..", 
		"Batch Job", MessageBoxButtons::OK);
	saveFileDialog1->Title = "Save Log File";		 
	saveFileDialog1->FileName = "log.txt";
	saveFileDialog1->OverwritePrompt = false;
	if(saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		String^ filename = saveFileDialog1->FileName;
		toolStripStatusLabel1->Text = "Executing Batch Jobs...";
		toolStripStatusLabel1->ToolTipText = "Executing Batch Jobs...";
		//executes the loaded batch jobs and prints log to this file
		if(!inv->executeBatch(Wrapper::toUnmanagedFileName(filename),*_curUser))
			MessageBox::Show(
			"Failed to execute file!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			MessageBox::Show(
			"Batch jobs executed.", 
			"Operation Successful.", MessageBoxButtons::OK, MessageBoxIcon::Information);
		toolStripStatusLabel1->Text = "Batch jobs executed.";
	}
	saveFileDialog1->OverwritePrompt = true;
}

/* Cancel load button */

void MainUI::backgroundWorkerCancelBtn_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) {
	if( e->KeyCode == Keys::Escape)
		e->IsInputKey = true;				 
	else e->IsInputKey = false;
}
void MainUI::backgroundWorkerCancelBtn_Leave(System::Object^  sender, System::EventArgs^  e) {
	backgroundWorkerCancelBtn->Focus();
}
void MainUI::backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {	
}

/* Shared functions */

void MainUI::selectAllMain(System::Object^  sender, System::EventArgs^  e) {
	TextBoxBase^ box = dynamic_cast<TextBoxBase^>(sender);				 
	if (!System::String::IsNullOrEmpty(box->Text))
	{
		box->SelectionStart = 0;
		box->SelectionLength = box->Text->Length;
	}
	box->Select();
}

void MainUI::MainUI_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	if(!inv->isSaved() && *_next == 0){
		System::Windows::Forms::DialogResult result = 
			MessageBox::Show(
			"Inventory has not been saved. Save changes to disk before closing?",
			"Warning", MessageBoxButtons::YesNoCancel,  MessageBoxIcon::Warning);
		if(result == System::Windows::Forms::DialogResult::Yes){
			saveInventoryToolStripMenuItem_Click(sender,e);
			if(!inv->isSaved()) e->Cancel = true;
		}
		else if(result == System::Windows::Forms::DialogResult::Cancel) e->Cancel = true;
	}
}