#include "stdafx.h"
#include "CashierUI.h"

using namespace Hypermarket;

/* UI Functions */
void CashierUI::CashierUI_Load(System::Object^  sender, System::EventArgs^  e) {				 
	this->Text = gcnew String(("CEG ICMS - Cashier [" + *_curUser + "]").c_str());
	resultgrp->Hide();
	resultsListView->Hide();
	searchType->SetItemChecked(0,true);
	searchBox->Focus();
}
void CashierUI::switchUIViews(){
	if(accounts->has_access(1,*_curUser)){
		*_next = 2;
		this->Close();
	}
	else{
		MessageBox::Show(
			"You do not have the required access level to use manager functions!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);	
	}

}
void CashierUI::searchType_TextClick(System::Object^  sender, System::EventArgs^  e) {
	searchType->SelectedIndex = -1;
	searchBox->Select();
}
void CashierUI::searchBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {				 
	if ( e->KeyChar == (char)13 ){
		gobtn->PerformClick();				 
		e->Handled = true;
	}
}
void CashierUI::selectAll(System::Object^  sender, System::EventArgs^  e) {
	selectAllMain(sender,e); // VS complains otherwise. does not allow inherited event method handlers -.-
}

/* Searching & Results functions */
void CashierUI::gobtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else{
		displayList->clear();
		String^ exactChar = gcnew String(L"\"");
		String^ searchStr = searchBox->Text;
		char type = 0x00;
		if(searchType->CheckedIndices->Contains(0))
			type += BARCODE;			 
		if(searchType->CheckedIndices->Contains(1))
			type += NAME;
		if(searchType->CheckedIndices->Contains(2))
			type += CATEGORY;		
		if(searchType->CheckedIndices->Contains(3))
			type += MANUFACTURER;	
		if(type == 0x00)
			MessageBox::Show(
			"No search type option selected!", 
			"Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		else if(searchStr->Length == 0){
			if(MessageBox::Show(
				"Empty search string entered!\nWould you like to display the whole inventory?", 
				"Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) ==  ::DialogResult::No){
					return;
			}
			else type = 0x15;
		}
		bool exact = false; 
		if(searchStr->StartsWith(exactChar) && searchStr->EndsWith(exactChar)){
			exact = true;
			searchStr = gcnew String( searchStr->Substring(1,searchStr->Length-2) );
		}
		inv->searchProducts(*displayList,Wrapper::toUnmanagedString(searchStr),type,exact);
		if(displayList->empty())						 
			MessageBox::Show(
			"No matching products found!", 
			"No matches", MessageBoxButtons::OK, MessageBoxIcon::Information);
		updateResults();
	}
}
void CashierUI::updateFields(int i){
	if(displayList->empty()){
		namebox->Text = L"";
		barcodebox->Text = L"";
		categorybox->Text = L"";
		manubox->Text = L"";
		pricebox->Text = L"";
		soldbox->Text = L"";
		stockbox->Text = L"";
		expirybox->Text = L"";
		discountbox->Text = L"";
	}
	else{					 
		namebox->Text = gcnew String((*displayList)[i]->getName().c_str());
		barcodebox->Text = gcnew String((*displayList)[i]->getBarcode().c_str());
		categorybox->Text = gcnew String((*displayList)[i]->getCategory().c_str());
		manubox->Text = gcnew String((*displayList)[i]->getManufacturer().c_str());
		pricebox->Text = String::Format("{0:C}",(*displayList)[i]->getPrice());
		stockbox->Text = gcnew String((*displayList)[i]->getNumStock().ToString());
		soldbox->Text = gcnew String((*displayList)[i]->getNumSold().ToString());
		if((*displayList)[i]->isPerishable()){					
			expirybox->Text = gcnew String(Date((*displayList)[i]->getExpiry()).formatted().c_str());

			discountbox->Text = String::Format("{0:P}",(*displayList)[i]->getDiscount()/100);
		}
		else{
			expirybox->Text = "N/A";
			discountbox->Text ="0.00%";
		}
	}
}
void CashierUI::updateResults(){
	if(displayList->size() < 2){
		resultgrp->Hide();
		resultsListView->Hide();
		updateFields(0);
	}
	else{
		resultsListView->Items->Clear();
		backgroundWorkerCancelBtn->Enabled = true;					 
		backgroundWorkerCancelBtn->Focus();
		toolStripProgressBar1->Visible = true;
		productgrp->Enabled = false;
		resultgrp->Enabled = false;
		searchgroup->Enabled = false;
		menuStrip1->Enabled = false;
		statusStrip1->Enabled = false;
		backgroundWorkerFillResults->RunWorkerAsync();		 
		resultsListView->ListViewItemSorter = gcnew ListViewItemComparer( 0, SortOrder::Ascending );	
		resultgrp->Show();					 
		resultsListView->Show();
	}
}
void CashierUI::backgroundWorkerFillResults_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {				 
	for(int i = 0; i < displayList->size(); i++){					 
		if (backgroundWorkerFillResults->CancellationPending){
			e->Cancel = true;
			break;
		}
		else{
			toolStripStatusLabel1->Text = i+"/"+displayList->size()+" items loaded...";
			toolStripProgressBar1->ToolTipText = i+"/"+displayList->size();
			toolStripProgressBar1->Value = ((i+1)*100)/displayList->size();
			ListViewItem^ tempItem = gcnew ListViewItem();
			tempItem->Tag = gcnew int(i);
			tempItem->Text = gcnew String((*displayList)[i]->getName().c_str());
			tempItem->SubItems->Add(gcnew String((*displayList)[i]->getCategory().c_str()));
			tempItem->SubItems->Add(gcnew String((*displayList)[i]->getManufacturer().c_str()));
			tempItem->SubItems->Add(gcnew String((*displayList)[i]->getBarcode().c_str()));
			resultsListView->Items->Add(tempItem);
		}
	}				 
	resultsListView->TopItem->Selected = true;
	toolStripStatusLabel1->Text = L"Search completed.";
}
void CashierUI::backgroundWorkerFillResults_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	productgrp->Enabled = true;
	resultgrp->Enabled = true;
	searchgroup->Enabled = true;
	menuStrip1->Enabled = true;
	statusStrip1->Enabled = true;
	backgroundWorkerCancelBtn->Enabled = false;
	toolStripProgressBar1->Visible = false;
	if(e->Cancelled)
		toolStripStatusLabel1->Text = L"Search cancelled.";
	searchBox->Focus();
}
void CashierUI::resultsListView_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	SortOrder type;
	if((dynamic_cast<ListViewItemComparer^>(resultsListView->ListViewItemSorter))->CurrentComparer() == e->Column){
		if((dynamic_cast<ListViewItemComparer^>(resultsListView->ListViewItemSorter))->CurrentSortOrder() == SortOrder::Descending)
			type = SortOrder::Ascending;
		else type = SortOrder::Descending;
	}
	else type = SortOrder::Ascending;
	resultsListView->ListViewItemSorter = gcnew ListViewItemComparer( e->Column , type );				 	
}
void CashierUI::resultsListView_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	ListView::SelectedListViewItemCollection^ items = resultsListView->SelectedItems;
	System::Collections::IEnumerator^ myEnum = items->GetEnumerator();
	while(myEnum->MoveNext()){
		int thisItem = System::Int32::Parse((safe_cast<ListViewItem^> (myEnum->Current))->Tag->ToString());					 
		updateFields(thisItem);					 
	}
}	
void CashierUI::backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {	
	if ( e->KeyChar == (char)27 ){
		if(backgroundWorkerFillResults->IsBusy)
			backgroundWorkerFillResults->CancelAsync();					
	}
	else e->Handled = true;
}


/* Modify item buttons */
bool CashierUI::btn_Click (Product*& product) {
	ListView::SelectedListViewItemCollection^ selectedItems = resultsListView->SelectedItems;
	System::Collections::IEnumerator^ myEnum = selectedItems->GetEnumerator();
	if (displayList->size()==0) {
		MessageBox::Show(
			"Error, no product listed!", "No selection", MessageBoxButtons::OK, MessageBoxIcon::Information);	
		return false;
	}
	if (displayList->size()==1)
		product = (*displayList)[0];
	if (displayList->size()>1) {
		while ( myEnum->MoveNext() )
		{
			ListViewItem^ curItem = safe_cast<ListViewItem^>(myEnum->Current);
			int selectedIndex = Int32::Parse(curItem->Tag->ToString());
			product = (*displayList)[selectedIndex];
		}
	}
	if (product==NULL) {
		MessageBox::Show(
			"Error, please select one of the products!", "No selection", MessageBoxButtons::OK, MessageBoxIcon::Information);	
		return false;
	}
	return true;
}
void CashierUI::restockbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	Product* product=NULL;
	if (btn_Click(product)) {
		RestockCashierDialogue^ popup = gcnew RestockCashierDialogue(inv,product);
		popup->ShowDialog();
		if(displayList->size()<2) updateFields(0);
		else resultsListView_SelectedIndexChanged(sender,e);
	}
	else return;
}
void CashierUI::sellbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	Product* product=NULL;
	if (btn_Click(product)) {
		SellCashierDialogue^ popup = gcnew SellCashierDialogue(inv,product);
		popup->ShowDialog();
		if(displayList->size()<2) updateFields(0);
		else resultsListView_SelectedIndexChanged(sender,e);
	}
	else return;
}