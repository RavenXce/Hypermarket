#include "stdafx.h"
#include "ManagerUI.h"

using namespace Hypermarket;

#pragma region UI Main Functions

void ManagerUI::ManagerUI_Load(System::Object^  sender, System::EventArgs^  e) {				 
	this->Text = gcnew String(("CEG ICMS - Manager [" + *_curUser + "]").c_str());
	searchType->SetItemChecked(0,true);
	resultsListViewInv->ListViewItemSorter = gcnew ListViewItemComparer( 0, SortOrder::Ascending );
	resultsListViewPrd->ListViewItemSorter = gcnew ListViewItemComparer( 0, SortOrder::None );
	resultsListViewManu->ListViewItemSorter = gcnew ListViewItemComparer( 0, SortOrder::None );
	resultsListViewAcc->ListViewItemSorter = gcnew ListViewItemComparer( 0, SortOrder::Ascending );
}
void ManagerUI::num_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}
void ManagerUI::switchUIViews(){
	*_next = 1;
	this->Close();
}
void ManagerUI::selectAll(System::Object^  sender, System::EventArgs^  e) {
	selectAllMain(sender,e); // VS complains otherwise. does not allow inherited event methods -.-
}
void ManagerUI::tabControl_Enter(System::Object^  sender, System::EventArgs^  e) {
	selectDefault();
}
void ManagerUI::tabControl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	selectDefault();
}
void ManagerUI::selectDefault(){
	if(tabControl->SelectedIndex == 0)
		searchBox->Focus();
	else if(tabControl->SelectedIndex == 1)
		numTopBox->Focus();
	else if(tabControl->SelectedIndex == 2)						 
		numTopManuBox->Focus();				 
	else if(tabControl->SelectedIndex == 3)
		nameAdd->Focus();
	else if(tabControl->SelectedIndex == 4){
		searchIDbox->Focus();
		resultsListViewAcc_Load();
	}
}
#pragma endregion
#pragma region Inventory Control Tab

void ManagerUI::searchBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		searchBtn->PerformClick();
		e->Handled = true;
	}				 
}
void ManagerUI::searchType_TextClick(System::Object^  sender, System::EventArgs^  e) {
	searchType->SelectedIndex = -1;
	searchBox->Focus();
}
void ManagerUI::searchBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else{
		invList->clear();
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
				"Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) ==  ::DialogResult::No)
			{
				return;
			}
			else type = 0x15;
		}
		bool exact = false; 
		if(searchStr->StartsWith(exactChar) && searchStr->EndsWith(exactChar)){
			exact = true;
			searchStr = gcnew String( searchStr->Substring(1,searchStr->Length-2) );
		}
		inv->searchProducts(*invList,Wrapper::toUnmanagedString(searchStr),type,exact);		
		updateResults(resultsListViewInv);					 
	}
	selectDefault();
}
void ManagerUI::resultsListViewInv_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	ColumnClick(sender,e);
}
#pragma endregion
#pragma region Top Products Tab

void ManagerUI::numTopBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// Start search if enter is hit
	if(e->KeyChar == (char)13) searchPrdBtn->PerformClick();
	// Accept only digits and the Backspace character
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}
void ManagerUI::filterBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		searchPrdBtn->PerformClick();
		e->Handled = true;
	}
}
void ManagerUI::catFilterBtn_Click(System::Object^  sender, System::EventArgs^  e) {			 
	if(catFilterBtn->Checked)
		catFilterBtn->Checked = false;
	else{ 
		catFilterBtn->Checked = true;
		if(manuFilterBtn->Checked)
			manuFilterBtn->Checked = false;
	}			 
	filterBox->Focus();
}
void ManagerUI::manuFilterBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(manuFilterBtn->Checked)
		manuFilterBtn->Checked = false;
	else{ 
		manuFilterBtn->Checked = true;
		if(catFilterBtn->Checked)
			catFilterBtn->Checked = false;
	}
	filterBox->Focus();
}
void ManagerUI::searchPrdBtn_Click(System::Object^  sender, System::EventArgs^  e) {				 
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else if(numTopBox->Text == "")
		MessageBox::Show(
		"Number ranks to display not selected!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else{
		int num = Int32::Parse(numTopBox->Text);
		revenueList->clear();
		if(filterBox->Text == "" || (!catFilterBtn->Checked && !manuFilterBtn->Checked))
			inv->findTopProducts(*revenueList,NULL,num);
		else{
			vector<Product*> filterList;
			String^ exactChar = gcnew String(L"\"");					 
			String^ searchStr = filterBox->Text;
			bool exact = false; 
			if(catFilterBtn->Checked)
				inv->searchProducts(filterList,Wrapper::toUnmanagedString(searchStr),CATEGORY,exact);
			else if(manuFilterBtn->Checked)
				inv->searchProducts(filterList,Wrapper::toUnmanagedString(searchStr),MANUFACTURER,exact);						 
			inv->findTopProducts(*revenueList,&filterList,num);
		}
		updateResults(resultsListViewPrd);
	}
	selectDefault();
}
void ManagerUI::resultsListViewPrd_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	ColumnClick(sender,e);		 	
}
#pragma endregion
#pragma region 	Top Manufacturers Tab

void ManagerUI::numTopManuBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	// Start search if enter is hit
	if(e->KeyChar == (char)13) searchManuBtn->PerformClick();
	// Accept only digits and the Backspace character
	if(!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08)
		e->Handled = true;
}
void ManagerUI::manuFilterBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		searchManuBtn->PerformClick();
		e->Handled = true;
	}
}
void ManagerUI::manuCheckBox_CheckStateChanged(System::Object^  sender, System::EventArgs^  e) {
	manuFilterBox->Focus();
}
void ManagerUI::searchManuBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else{
		int num = Int32::Parse(numTopManuBox->Text);
		manuList->clear();
		if(manuFilterBox->Text == "" || !(manuFilterCheck->Checked))
			inv->findBestManufacturer(*manuList,NULL,num);
		else{
			vector<Product*> filterList;
			String^ exactChar = gcnew String(L"\"");					 
			String^ searchStr = manuFilterBox->Text;
			bool exact = false; 
			if(searchStr->StartsWith(exactChar) && searchStr->EndsWith(exactChar)){
				exact = true;
				searchStr = gcnew String( searchStr->Substring(1,searchStr->Length-2) );
			}
			inv->searchProducts(filterList,Wrapper::toUnmanagedString(searchStr),CATEGORY,exact);
			inv->findBestManufacturer(*manuList,&filterList,num);
		}
		updateResults(resultsListViewManu);
	}
	selectDefault();
}
void ManagerUI::resultsListViewManu_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	ColumnClick(sender,e);		 
}
#pragma endregion
#pragma region Batch Jobs Tab

void ManagerUI::addbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	bool mask = false;
	DateTime^ curDateTime = DateTime::Now;
	String^ curDate =  curDateTime->Day.ToString("00") + curDateTime->Month.ToString("00") + curDateTime->Year.ToString("0000");
	queue<string> temp;
	BatchJob* newJob = NULL;
	switch(tabcontrol1->SelectedIndex){
	case 0: //ADD
		if(barcodeAdd->Text != "" && nameAdd->Text != "" && categoryAdd->Text != ""
			&& manufacturerAdd->Text != "" && numStockAdd->Text != "" && priceAdd->Text != "")
		{
			if(priceAdd->Text->IndexOf('.') != priceAdd->Text->LastIndexOf('.')){
				MessageBox::Show(
					"Invalid price format!", 
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			newJob = new BatchJobAdd("ADD",
				Wrapper::toUnmanagedString(barcodeAdd->Text),
				Wrapper::toUnmanagedString(nameAdd->Text),
				Wrapper::toUnmanagedString(categoryAdd->Text),
				Wrapper::toUnmanagedString(priceAdd->Text),
				Wrapper::toUnmanagedString(manufacturerAdd->Text),
				Wrapper::toUnmanagedString(numStockAdd->Text));
		} break;
	case 1: //DELETE
		if(barcodeDelete->Text != "")
			newJob = new BatchJobDelete("DELETE",Wrapper::toUnmanagedString(barcodeDelete->Text));
		break;
	case 2: //RESTOCK
		if(barcodeRestock->Text != ""&& numAddRestock->Text != "")
			newJob = new BatchJobRestock("RESTOCK",Wrapper::toUnmanagedString(barcodeRestock->Text),Wrapper::toUnmanagedString(numAddRestock->Text));
		break;
	case 3: //DISPOSE
		if(barcodeDispose->Text != "")
			newJob = new BatchJobDispose("DISPOSE",Wrapper::toUnmanagedString(barcodeDispose->Text),Wrapper::toUnmanagedString(curDate));
		break;
	case 4: //DISPOSE ALL
		newJob = new BatchJobDisposeAll("DISPOSEALL",Wrapper::toUnmanagedString(curDate));
		break;
	case 5: //SALE
		if(barcodeSale->Text != "" && numSoldSale->Text != "")
			newJob = new BatchJobSale("SALE",Wrapper::toUnmanagedString(barcodeSale->Text),Wrapper::toUnmanagedString(numSoldSale->Text));
		break;
	case 6: //DISCOUNT
		if(daysLeftDiscount->Text != "" && discountDiscount->Text != "")
		{
			if(discountDiscount->Text->IndexOf('.') != discountDiscount->Text->LastIndexOf('.')){
				MessageBox::Show(
					"Invalid discount format!", 
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			if(Double::Parse(discountDiscount->Text) < 0 || Double::Parse(discountDiscount->Text) > 100){
				MessageBox::Show(
					"Invalid discount range! Please enter a valid range between 0 and 100.", 
					"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			newJob = new BatchJobDiscount("DISCOUNT",Wrapper::toUnmanagedString(daysLeftDiscount->Text),Wrapper::toUnmanagedString(discountDiscount->Text));
		} break;
	case 7: //RESTOCK MANU
		if(numAddRestockManufacturer->Text != "" && manufacturerRestockManufacturer->Text != "")
		{	
			newJob = new BatchJobRestockManufacturer("RESTOCKMANUFACTURER",
				Wrapper::toUnmanagedString(manufacturerRestockManufacturer->Text),
				Wrapper::toUnmanagedString(numAddRestockManufacturer->Text));
		} break;
	case 8: //RESTOCK CAT
		if(numAddRestockCategory->Text != "" && categoryRestockCategory->Text != "")
			newJob = new BatchJobRestockCategory("RESTOCKCATEGORY",
			Wrapper::toUnmanagedString(categoryRestockCategory->Text),
			Wrapper::toUnmanagedString(numAddRestockCategory->Text));
		break;
	case 9: //RESTOCK LEFT
		if(numAddRestockLeft->Text != "" && leftRestockLeft->Text != "")
			newJob = new BatchJobRestockLeft("RESTOCKLEFT",Wrapper::toUnmanagedString(leftRestockLeft->Text),Wrapper::toUnmanagedString(numAddRestockLeft->Text));
		break;
	}
	if(newJob==NULL){
		MessageBox::Show(
			"Not all fields were filled!", 
			"Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else{
		if(inv->addNewJob(newJob)){
			MessageBox::Show(
				"Job added!", 
				"Operation Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
			numjobsaddedbox->Text =  (Int32::Parse(numjobsaddedbox->Text)+1).ToString();
		}
		else
			MessageBox::Show(
			"An error occured: failed to add batch jobs.", 
			"Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
void ManagerUI::finishbtn_Click(System::Object^  sender, System::EventArgs^  e) {		
	saveFileDialog1->Title = "Save Batch Jobs To File";		 
	saveFileDialog1->FileName = "batchjobs.txt";
	saveFileDialog1->OverwritePrompt = false;
	if(saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
		String^ filename = saveFileDialog1->FileName;
		toolStripStatusLabel1->Text = "Saving Batch Jobs File...";
		toolStripStatusLabel1->ToolTipText = "Saving Batch Jobs File...";
		if(inv->addBatchJob(Wrapper::toUnmanagedFileName(filename),*user))
			MessageBox::Show(
			"Jobs saved successfully!", 
			"Operation Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
		else
			MessageBox::Show(
			"Failed to save batch jobs.", 
			"Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		saveFileDialog1->OverwritePrompt = true;
		toolStripStatusLabel1->Text = "Inventory saved.";
	}
	numjobsaddedbox->Text = "0";
}
void ManagerUI::priceAdd_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar!='.')
		num_KeyPress(sender,e);
}
#pragma endregion
#pragma region User Accounts Tab

void ManagerUI::resultsListViewAcc_Load(){				 
	*accountsList = accounts->get_accounts();
	resultsListViewAcc->Items->Clear();
	for(int i =0; i<(*accountsList).size(); i++){
		ListViewItem^ tempItem = gcnew ListViewItem();				 
		String^ userID = gcnew String(((*accountsList)[i].second.c_str()));
		if(userID->Contains(searchIDbox->Text)){
			tempItem->Tag = i;
			if((*accountsList)[i].first==0)
				tempItem->Text = "Cashier";
			else if((*accountsList)[i].first==1)
				tempItem->Text = "Manager";
			else
				tempItem->Text = "Unknown";
			tempItem->SubItems->Add(userID);					 
			resultsListViewAcc->Items->Add(tempItem);
		}
		else delete tempItem;
	}
}
void ManagerUI::addaccountbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	int level = 0;
	if(radiobtnManager->Checked) level = 1;				 
	string userID = Wrapper::toUnmanagedString(userIDbox->Text);
	string password = Wrapper::toUnmanagedString(passwordbox->Text);
	if(userID.empty()){
		MessageBox::Show(
			"UserID field is empty!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if(password.empty()){
		MessageBox::Show(
			"Password field is empty!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if(password.size() < 6){
		MessageBox::Show(
			"Password field is too short!", 
			"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if(accounts->add_account(level,userID,password))
		MessageBox::Show(
		"Account added!", 
		"Success", MessageBoxButtons::OK);
	else 
		MessageBox::Show(
		"Account name already exists!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	resultsListViewAcc_Load();				 
}
void ManagerUI::deleteAccountToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if(MessageBox::Show(
		"Delete the selected accounts?", 
		"Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) ==  ::DialogResult::Yes)
	{
		ListView::SelectedListViewItemCollection^ selectedItems = resultsListViewAcc->SelectedItems;
		bool success = true;
		System::Collections::IEnumerator^ myEnum = selectedItems->GetEnumerator();
		while ( myEnum->MoveNext() )
		{
			ListViewItem^ curItem = safe_cast<ListViewItem^>(myEnum->Current);
			int selectedIndex = Int32::Parse(curItem->Tag->ToString());
			if(*_curUser == (*accountsList)[selectedIndex].second){
				MessageBox::Show(
					"Cannot delete the currently accessed account!", 
					"Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}						 
		}
		myEnum->Reset();
		while ( myEnum->MoveNext() )
		{
			ListViewItem^ curItem = safe_cast<ListViewItem^>(myEnum->Current);
			int selectedIndex = Int32::Parse(curItem->Tag->ToString());
			if(!accounts->delete_account((*accountsList)[selectedIndex].second)) success = false;
			else resultsListViewAcc->Items->Remove(curItem);
		}
		if(success)
			MessageBox::Show(
			"Accounts deleted!", 
			"Operation Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
		else
			MessageBox::Show(
			"An error occured while trying to delete the seleted accounts.", 
			"Operation Unsuccessful", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
void ManagerUI::saveddbbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(accounts->save_pw_data("accounts.txt"))
		MessageBox::Show(
		"Account database saved.", 
		"User Accounts", MessageBoxButtons::OK, MessageBoxIcon::Information);
	else
		MessageBox::Show(
		"An error occured: Failed to save to database file!", 
		"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
}
void ManagerUI::cleardbbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	if(MessageBox::Show(
		"Reset changes?", 
		"Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) ==  ::DialogResult::Yes){
			accounts->load_pw_data("accounts.txt");
			resultsListViewAcc_Load();
	}
}
void ManagerUI::radiobtnCashier_Click(System::Object^  sender, System::EventArgs^  e) {
	radiobtnCashier->Checked = true;
	radiobtnManager->Checked = false;
}
void ManagerUI::radiobtnManager_Click(System::Object^  sender, System::EventArgs^  e) {
	radiobtnCashier->Checked = false;
	radiobtnManager->Checked = true;
}
void ManagerUI::userIDbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		passwordbox->Focus();
		e->Handled = true;
	}
}
void ManagerUI::passwordbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		addaccountbtn->PerformClick();
		e->Handled = true;
	}
}
void ManagerUI::searchIDbox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if(e->KeyChar == (char)13){
		searchidbtn->PerformClick();
		e->Handled = true;
	}
}
void ManagerUI::searchidbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	resultsListViewAcc_Load();
}
void ManagerUI::resultsListViewAcc_ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	ColumnClick(sender,e);
}
#pragma endregion
#pragma region Results Windows

void ManagerUI::updateResults(ListView^ resultWindow){				 
	resultWindow->Items->Clear();
	if((resultWindow == resultsListViewInv && invList->empty()) ||
		(resultWindow == resultsListViewPrd && revenueList->empty()) || 
		(resultWindow == resultsListViewManu && manuList->empty()) )
	{
		MessageBox::Show(
			"No matching products found!", 
			"No matches", MessageBoxButtons::OK, MessageBoxIcon::Information);					 
		if(resultWindow == resultsListViewInv)
			searchBox->Focus();
		else if(resultWindow == resultsListViewPrd)
			filterBox->Focus();
		else if (resultWindow == resultsListViewManu)
			manuFilterBox->Focus();
	}
	else
	{
		backgroundWorkerCancelBtn->Enabled = true;					 
		backgroundWorkerCancelBtn->Focus();
		toolStripProgressBar1->Visible = true;
		tabControl->Enabled = false;
		resultgrpPrd->Enabled = false;
		searchgrpPrd->Enabled = false;
		menuStrip1->Enabled = false;
		statusStrip1->Enabled = false;
		backgroundWorkerFillResults->RunWorkerAsync(resultWindow);
		SortOrder order;
		if(resultWindow == resultsListViewInv) order = SortOrder::Ascending;		// name sort
		else order = SortOrder::None;												// revenue sort
		resultWindow->ListViewItemSorter = gcnew ListViewItemComparer( 0, order );
		resultWindow->Show();
	}
}
void ManagerUI::backgroundWorkerFillResults_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	ListView^ resultWindow = safe_cast<ListView^>(e->Argument);
	Product * item = NULL;
	int size;
	if(resultWindow == resultsListViewInv) size = invList->size();
	else if(resultWindow == resultsListViewPrd) size = revenueList->size();			
	else if(resultWindow == resultsListViewManu) size = manuList->size();
	for(int i = 0; i < size; i++){					 
		if (backgroundWorkerFillResults->CancellationPending){
			e->Cancel = true;
			break;
		}
		else{
			toolStripStatusLabel1->Text = i+"/"+size+" items loaded...";
			toolStripProgressBar1->ToolTipText = i+"/"+size;
			toolStripProgressBar1->Value = ((i+1)*100)/size;
			ListViewItem^ tempItem = gcnew ListViewItem();
			tempItem->Tag = gcnew int(i);
			if(resultWindow == resultsListViewManu){
				tempItem->Text = gcnew String(String::Format("{0:C}",(*manuList)[i].second));
				tempItem->SubItems->Add(gcnew String((*manuList)[i].first.c_str()));
			}
			else{
				if(resultWindow == resultsListViewInv){
					item = (*invList)[i];				
					tempItem->Text = gcnew String(item->getName().c_str());
				}
				else if(resultWindow == resultsListViewPrd){
					item = (*revenueList)[i].first;
					tempItem->Text = gcnew String(String::Format("{0:C}",(*revenueList)[i].second));
					tempItem->SubItems->Add(gcnew String(item->getName().c_str()));	
				}
				tempItem->SubItems->Add(gcnew String(item->getCategory().c_str()));
				tempItem->SubItems->Add(gcnew String(item->getManufacturer().c_str()));							 
				tempItem->SubItems->Add(gcnew String(String::Format("{0:C}",item->getPrice())));
				tempItem->SubItems->Add(gcnew String(String::Format("{0:P}",item->getDiscount()/100)));							 
				tempItem->SubItems->Add(gcnew String(item->getNumSold().ToString()));
				tempItem->SubItems->Add(gcnew String(item->getNumStock().ToString()));
				if(item->isPerishable())
					tempItem->SubItems->Add(gcnew String(Date(item->getExpiry()).formatted().c_str()));
				else
					tempItem->SubItems->Add(gcnew String("N/A"));
				tempItem->SubItems->Add(gcnew String(item->getBarcode().c_str()));					 
			}
			resultWindow->Items->Add(tempItem);
		}
	}
	toolStripStatusLabel1->Text = L"Search completed.";
}		
void ManagerUI::backgroundWorkerFillResults_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	tabControl->Enabled = true;
	resultgrpPrd->Enabled = true;
	searchgrpPrd->Enabled = true;
	menuStrip1->Enabled = true;
	statusStrip1->Enabled = true;
	backgroundWorkerCancelBtn->Enabled = false;
	toolStripProgressBar1->Visible = false;
	if(e->Cancelled)
		toolStripStatusLabel1->Text = L"Search cancelled.";
	numTopBox->Focus();
}
void ManagerUI::ColumnClick(System::Object^  sender, System::Windows::Forms::ColumnClickEventArgs^  e) {
	SortOrder type;
	ListView^ resultWindow = safe_cast<ListView^>(sender);
	if(e->Column == 0 && resultWindow != resultsListViewInv && resultWindow != resultsListViewAcc) 
		type = SortOrder::None; // revenue (currency-type) sort
	else if((safe_cast<ListViewItemComparer^>(resultWindow->ListViewItemSorter))->CurrentComparer() == e->Column){
		if((safe_cast<ListViewItemComparer^>(resultWindow->ListViewItemSorter))->CurrentSortOrder() == SortOrder::Descending)
			type = SortOrder::Ascending;
		else type = SortOrder::Descending;
	}
	else type = SortOrder::Ascending;
	resultWindow->ListViewItemSorter = gcnew ListViewItemComparer( e->Column , type );
}
void ManagerUI::backgroundWorkerCancelBtn_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {	
	if ( e->KeyChar == (char)27 ){
		if(backgroundWorkerFillResults->IsBusy)
			backgroundWorkerFillResults->CancelAsync();					
	}
	else e->Handled = true;		
}
#pragma endregion
#pragma region Inventory Control Caller Functions

void ManagerUI::resultContextMenu_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	if(resultsListViewInv->SelectedIndices->Count > 0){
		deleteProductToolStripMenuItem->Visible = true;
		if(resultsListViewInv->SelectedIndices->Count <= 1)
			editProductToolStripMenuItem->Visible = true;
		else editProductToolStripMenuItem->Visible = false;
	}
	else deleteProductToolStripMenuItem->Visible = false;			
}
void ManagerUI::resultsListViewInv_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	editProductToolStripMenuItem_Click(sender,e);
}
void ManagerUI::perishableToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	ProductModUI^ popup = gcnew ProductModUI(inv,NULL,PERISH);
	popup->ShowDialog();
	delete popup;
}
void ManagerUI::nonPerishableToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if(!inv->isLoaded())
		MessageBox::Show(
		"No inventory has been loaded!", 
		"Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	ProductModUI^ popup = gcnew ProductModUI(inv,NULL,NPERISH);
	popup->ShowDialog();
	delete popup;
}
void ManagerUI::editProductToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	ListView::SelectedListViewItemCollection^ selectedItems = resultsListViewInv->SelectedItems;
	System::Collections::IEnumerator^ myEnum = selectedItems->GetEnumerator();
	Product* product = NULL;
	ListViewItem^ curItem;
	while ( myEnum->MoveNext() )
	{
		curItem = safe_cast<ListViewItem^>(myEnum->Current);
		int selectedIndex = Int32::Parse(curItem->Tag->ToString());
		product = (*invList)[selectedIndex];
	}
	ProductModUI^ popup = gcnew ProductModUI(inv,product,product->isPerishable());				 	
	popup->ShowDialog();
	//update item
	curItem->SubItems->Clear();				 
	curItem->Text = gcnew String(product->getName().c_str());	 
	curItem->SubItems->Add(gcnew String(product->getCategory().c_str()));
	curItem->SubItems->Add(gcnew String(product->getManufacturer().c_str()));							 
	curItem->SubItems->Add(gcnew String(String::Format("{0:C}",product->getPrice())));
	curItem->SubItems->Add(gcnew String(String::Format("{0:P}",product->getDiscount()/100)));							 
	curItem->SubItems->Add(gcnew String(product->getNumSold().ToString()));
	curItem->SubItems->Add(gcnew String(product->getNumStock().ToString()));
	if(product->isPerishable())
		curItem->SubItems->Add(gcnew String(Date(product->getExpiry()).formatted().c_str()));
	else
		curItem->SubItems->Add(gcnew String("N/A"));
	curItem->SubItems->Add(gcnew String(product->getBarcode().c_str()));
	resultsListViewInv->Refresh();
}
void ManagerUI::deleteProductToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if(MessageBox::Show(
		"Delete the selected products?", 
		"Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation) ==  ::DialogResult::Yes)
	{
		ListView::SelectedListViewItemCollection^ selectedItems = resultsListViewInv->SelectedItems;
		bool success = true;
		System::Collections::IEnumerator^ myEnum = selectedItems->GetEnumerator();
		while ( myEnum->MoveNext() )
		{
			ListViewItem^ curItem = safe_cast<ListViewItem^>(myEnum->Current);
			int selectedIndex = Int32::Parse(curItem->Tag->ToString());
			if(!inv->deleteProduct((*invList)[selectedIndex]->getBarcode())) success = false;
			else resultsListViewInv->Items->Remove(curItem);
		}
		if(success)
			MessageBox::Show(
			"Items deleted!", 
			"Operation Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
		else
			MessageBox::Show(
			"An error occured while trying to delete the selected products.", 
			"Operation Unsuccessful", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
#pragma endregion	
