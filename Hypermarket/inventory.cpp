#include "stdafx.h"
#include "inventory.h"
#include "wrapper.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cassert>
#include <ctime>
#include <iomanip>
#include <list>

using namespace std;
typedef map<string,Product*> maptype;

Inventory::Inventory(){ _loaded = false; }
// returns true if inv has been loaded from file or a product is added, false if no file has been loaded and inv is empty
bool Inventory::isLoaded(){	return _loaded; }
bool Inventory::isSaved(){	return _saved; }
bool Inventory::batchLoaded(){ return _batch.empty() ? 0 : 1; }
void Inventory::unloadInventory(){ return _inv.clear(); }

/********************************* FILE IO FUNCTIONS *********************************/
#pragma region FileIOFunctions

bool Inventory::loadInventory(char *filename){
	int size;
	char input;
	string name, category, barcode, manufacturer;
	double price, discount;
	unsigned int numstock,numsold, expiry;
	bool perishable;
	
	ifstream inFile;
	inFile.open(filename);
	if(inFile.fail()) return false;
	inFile >> size;
	for(int i=0; i<size; i++){
		inFile >> input;
		if(tolower(input) == 'y') perishable = true;
		else perishable = false;
		inFile.get();
		getline(inFile,name);
		getline(inFile,category);
		inFile >> barcode >> price;
		inFile.get();
		getline(inFile,manufacturer);
		inFile >> numstock >> numsold;
		if(!perishable) addProduct(Product(name,category,barcode,manufacturer,price,numstock,numsold));
		else{
			inFile >> expiry >> discount;
			addProduct(PerishableProduct(name,category,barcode,manufacturer,price,numstock,numsold,expiry,discount));
		}
	}
	inFile.close();
	_loaded = true;
	_saved = true;
	return true;
}
bool Inventory::loadBatchfile(char *filename){
	int size,num;
	string username,option,temp;
	int choice = 0;
	string name,category,barcode,price,manufacturer,numstock,numadd,curdate,numsold,days,discount,numleft;
	ifstream inFile;
	while(!_batch.empty()) _batch.pop(); // clear loaded batch
	inFile.open(filename);
	if(inFile.fail()) return false;
	inFile >> num;
	inFile.get();
	for(int j=0;j<num;j++){
		queue<BatchJob *> tempJob;
		getline(inFile,username);
		inFile >> size;
		inFile.get();
		for(int i=0; i<size; i++){
			choice = 0;
			getline(inFile,option);
			if(option == "ADD") choice = 1;
			else if(option == "DELETE") choice = 2;
			else if(option == "RESTOCK") choice = 3;
			else if(option == "DISPOSE") choice = 4;
			else if(option == "SALE") choice = 5;
			else if(option == "DISCOUNT") choice = 6;
			else if(option == "DISPOSEALL") choice = 7;
			else if(option == "RESTOCKMANUFACTURER") choice = 8;
			else if(option == "RESTOCKCATEGORY") choice = 9;
			else if(option == "RESTOCKLEFT") choice = 10;

			assert(choice != 0);
			BatchJob* tempString;
			switch(choice){
			case 1:
				getline(inFile,name);
				getline(inFile,category);
				getline(inFile,barcode);
				getline(inFile,price);
				getline(inFile,manufacturer);
				getline(inFile,numstock);
				tempString = new BatchJobAdd(option,barcode,name,category,price,manufacturer,numstock);
				break;
			case 2:
				getline(inFile,barcode);
				tempString = new BatchJobDelete(option,barcode);
				break;
			case 3:
				getline(inFile,barcode);
				getline(inFile,numadd);
				tempString = new BatchJobRestock(option,barcode,numadd);
				break;
			case 4:
				getline(inFile,barcode);
				getline(inFile,curdate);
				tempString = new BatchJobDispose(option,barcode,curdate);
				break;
			case 5:
				getline(inFile,barcode);
				getline(inFile,numsold);
				tempString = new BatchJobSale(option,barcode,numsold);
				break;
			case 6:
				getline(inFile,days);
				getline(inFile,discount);
				tempString = new BatchJobDiscount(option,days,discount);
				break;
			case 7:
				getline(inFile,curdate);
				tempString = new BatchJobDisposeAll(option,curdate);
				break;
			case 8:
				getline(inFile,manufacturer);
				getline(inFile,numadd);
				tempString = new BatchJobRestockManufacturer(option,manufacturer,numadd);
				break;
			case 9:
				getline(inFile,category);
				getline(inFile,numadd);
				tempString = new BatchJobRestockCategory(option,category,numadd);
				break;
			case 10:
				getline(inFile,numleft);
				getline(inFile,numadd);
				tempString = new BatchJobRestockLeft(option,numleft,numadd);
				break;
			}
			tempJob.push(tempString);
		}
		_batch.push(make_pair(username,tempJob));
	}
	inFile.close();	
	return true;
}
bool Inventory::saveInventory(char *filename){
	int size;
	Product* cur = NULL;

	ofstream outFile;
	outFile.open(filename,ios::trunc);
	if(outFile.fail()) return false;

	size = _inv.size();

	outFile << size;
	maptype::iterator mapIt = _inv.begin();
	for(; mapIt != _inv.end(); mapIt++){
		cur = &(*mapIt->second);
		assert(cur != NULL);
		outFile << endl;
		if(cur->isPerishable()) outFile << 'y' << endl;
		else outFile << 'n' << endl;
		outFile << cur->getName() << endl << cur->getCategory() << endl << cur->getBarcode() << endl << cur->getPrice() << endl << cur->getManufacturer() << endl
			<< cur->getNumStock() << endl << cur->getNumSold();
		if(cur->isPerishable())
			outFile << endl  << setfill('0') << setw(8) << cur->getExpiry() << endl << cur->getDiscount();
	}
	outFile.close();
	_saved = true;
	return true;
}
#pragma endregion
/********************************* END OF FILE IO *********************************/

/********************************* INVENTORY CONTROL FUNCTIONS *********************************/
#pragma region Inventory Control Functions

void Inventory::productModified() { _saved = false; }

bool Inventory::addProduct(Product &insert){
	Product *product = insert.clone();
	if(_inv.find(insert.getBarcode())==_inv.end())
	{
		_inv.insert(make_pair(insert.getBarcode(),product));
		_saved = false;
		_loaded = true;
		return true;
	}
	else return false;
}

bool Inventory::deleteProduct(string barcode){
	if(_inv.find(barcode)!=_inv.end()){
		_inv.erase(_inv.find(barcode));
		_saved = false;
		return true;
	}
	else return false;
}

bool Inventory::restockProduct(string barcode, unsigned num){
	Product* product = findProduct(barcode);
	if(product!=NULL){
		product->changeNumStock(num);
		_saved = false;
		return true;
	}
	else return false;
}

bool Inventory::resetSalesCount(string barcode) {
	Product* product = findProduct(barcode);
	if(product!=NULL){
		product->resetNumSold();
		_saved = false;
		return true;
	}
	else return false;
}

bool Inventory::sellProduct(string barcode, unsigned int num){
	Product* product = findProduct(barcode);
	if(product!=NULL && product->getNumStock() >= num){
		product->sell(num);
		_saved = false;
		return true;
	}
	else return false;
}

//deprecated
int Inventory::checkProductExpiry(string barcode) {
	Product* product = findProduct(barcode);
	string curTime;
	if(product == NULL) return -2;
	if(!product->isPerishable()) return -1;
	else{
		Date cur;
		Date exp(product->getExpiry());
		if(exp-cur > 0) return exp-cur;
		else return 0;
	}
}
//deprecated
Product* Inventory::findProduct(string barcode){
	Product* product = NULL;
	if(_inv.find(barcode)!=_inv.end()){
		product = _inv.find(barcode)->second;
		return product;
	}
	return NULL;
}
#pragma endregion
/********************************* END OF INVENTORY CONTROL *********************************/

/********************************* STATISTICS FUNCTIONS *********************************/
#pragma region Statistics Functions
bool Inventory::findTopProducts(vector<pair<Product*,double>>& retList, const vector<Product*> *searchList, int x){
	Product *curProduct = NULL;
	multimap<double,Product*> sortMap;
	multimap<double,Product*>::iterator mapIt;
	// if searchList is not given, sort entire inventory
	if(searchList == NULL){
		if(_inv.size() == 0) return false;
		maptype::iterator mapIt = _inv.begin();
		for(; mapIt != _inv.end(); mapIt++){
			curProduct = mapIt->second;
			assert(curProduct != NULL);
			double thisRevenue = curProduct->getPrice()*((100+curProduct->getDiscount())/100)*curProduct->getNumSold();
			sortMap.insert(make_pair(thisRevenue,curProduct));
		}
	}
	// else sort searchList
	else{
		if(searchList->size()==0) return false;
		for(int i = 0; i < searchList->size(); i++){
			double thisRevenue = ((*searchList)[i]->getPrice()) * ((100+((*searchList)[i]->getDiscount()))/100) * ((*searchList)[i]->getNumSold());
			sortMap.insert(make_pair(thisRevenue,(*searchList)[i]));
		}
	}
	// put sorted elements into return list
	for(--(mapIt = sortMap.end()); retList.size() < x && mapIt != (--sortMap.begin()); mapIt--)
		retList.push_back(make_pair(mapIt->second,mapIt->first));
	// add ties for last place into return list
	if(mapIt != (--sortMap.begin()))
		for(;retList.back().second == mapIt->first && mapIt != (--sortMap.begin()); mapIt--)
			retList.push_back(make_pair(mapIt->second,mapIt->first));
	return true;
}

bool Inventory::findBestManufacturer(vector<pair<string,double>>& retList, const vector<Product*> *searchList, int num){
	Product* product = NULL;
	list<pair<string,double>> sortedList;
	list<pair<string,double>>::iterator listIt;
	map<string,double> manuList;
	map<string,double>::iterator it;
	if(_inv.size() == 0) return false;
	string key;
	double val;
	if(searchList == NULL){
		maptype::iterator mapIt = _inv.begin();
		for(; mapIt != _inv.end(); mapIt++){
			product = mapIt->second;
			assert(product != NULL);
			key = product->getManufacturer();
			val = product->getPrice()*((100+product->getDiscount())/100)*product->getNumSold();
			it = manuList.find(product->getManufacturer());
			if(it == manuList.end()) manuList.insert(make_pair(key,val));
			else it->second += val;
		}
	}
	else{
		for(int i=0; i < searchList->size(); i++){
			product = (*searchList)[i];
			assert(product != NULL);
			key = product->getManufacturer();
			val = product->getPrice()*((100+product->getDiscount())/100)*product->getNumSold();
			it = manuList.find(product->getManufacturer());
			if(it == manuList.end()) manuList.insert(make_pair(key,val));
			else it->second += val;
		}
	}
	// sort manu map into return list
	bool added;
	for(it = manuList.begin(); it != manuList.end(); it++){
		added = false;
		for(listIt = sortedList.begin(); listIt != sortedList.end(); listIt++){
			if(it->second > listIt->second){
				sortedList.insert(listIt,make_pair(it->first,it->second));
				added = true;
				break;
			}
		}
		if(!added) sortedList.push_back(make_pair(it->first,it->second));
	}
	// copy to return vector
	for(listIt = sortedList.begin(); listIt != sortedList.end() && retList.size() < num; listIt++)
		retList.push_back(*listIt);
	for(; listIt != sortedList.end() && listIt->second == retList.back().second; listIt++)
		retList.push_back(*listIt);
	return true;
}

bool Inventory::searchProducts(vector<Product*> &retList, string str, char type, bool exact){
	//type 0x08 = manufacturer, 0x04 = category, 0x02 = name, 0x01 = barcode
	//return list of products with attribute of specified type matching str
	Product* product = NULL;
	maptype::iterator mapIt = _inv.begin();
	for(; mapIt != _inv.end(); mapIt++){
		product = mapIt->second;
		assert(product != NULL);
		// do substring match for appropriate attribute
		if( ( (type & 0x08) && strmatch(product->getManufacturer(),str,exact) )||
			( (type & 0x04) && strmatch(product->getCategory(),str,exact) )||
			( (type & 0x02) && strmatch(product->getName(),str,exact) )||
			( (type & 0x01) && product->getBarcode() == str) )
		retList.push_back(product);
	}
	if(retList.size() == 0) return false;
	return true;
}

bool Inventory::strmatch(string str1, string str2, bool exact){
	// matches two strings, returns true if a string is found in the other (or vice versa).
	if(str1.size() < str2.size())
		return strmatch(str2,str1,exact);
	transform(str1.begin(),str1.end(),str1.begin(),tolower);	
	transform(str2.begin(),str2.end(),str2.begin(),tolower);
	if(!exact){
		if(strstr(str1.c_str(),str2.c_str()) == NULL) return false;
		else return true;
	}
	else if(str1 != str2) return false;
	else return true;
}
#pragma endregion
/********************************* END OF STATISTICS *********************************/

/********************************* BATCH FUNCTIONS *********************************/
#pragma region Batch Functions
bool Inventory::executeBatch(char *filename, string username)
{
	int size_1 = _batch.size(); // size_1 is the number of users
	for(int i=0;i<size_1;i++){
		int size_2 = _batch.top().second.size(); //size_2 is the number of jobs per user
		for(int j=0;j<size_2;j++){
			_batch.top().second.front()->execute(_inv,_log,_batch.top().first);
			_batch.top().second.pop();
		}
		_batch.pop();
	}
	if(generateLogFile("log.txt", username))
		return true;
	else
		return false;
}
// add new job for user to queue
bool Inventory::addNewJob(BatchJob* addNewJob)
{
	_newJobs.push(addNewJob);
	return true;
}
//add all new jobs for user to file
bool Inventory::addBatchJob(const string & filename, const string &username)
{
	bool mask = true;
	int numOfUser,size1,size2;
	Product* cur = NULL;
	stack<pair<string,queue<BatchJob *>>> batchCopy;

	ifstream inFile;	ofstream outFile;
	inFile.open(filename,ios::_Nocreate);
	if(inFile.fail()) 
	{
		// if new file save currently loaded batch data to file also first
		inFile.close();
		outFile.open(filename,ios::trunc);
		outFile<<_batch.size()+1<<endl;
		size1 = _batch.size();
		for(;size1>0;size1--)
		{
			batchCopy.push(_batch.top());
			_batch.pop();
		}
		size1 = batchCopy.size();
		for(;size1>0;size1--)
		{
			outFile<<batchCopy.top().first<<endl;
			size2 = batchCopy.top().second.size();
			outFile<<size2<<endl;
			_batch.push(batchCopy.top());
			for(;size2>0;size2--)
			{
				copy(batchCopy.top().second.front()->list.begin(),batchCopy.top().second.front()->list.end(), ostream_iterator<string>(outFile,"\n"));
				batchCopy.top().second.pop();
			}
			batchCopy.pop();
		}
	}
	else // check number of users and go to end of file
	{
		inFile.seekg(0,ios::beg);
		inFile>>numOfUser;
		inFile.seekg(-1,ios::end);
		char check_newline;
		inFile >> check_newline;
		inFile.close();
		outFile.open(filename,ios::_Nocreate);
		outFile.seekp(0,ios::beg);
		outFile<<numOfUser+1;
		outFile.seekp(-1,ios::end);
		if(check_newline != '\n') outFile << endl;
	}
	outFile<<username<<endl;
	queue<BatchJob*> temp;
	outFile<<_newJobs.size()<<endl;
	while(!_newJobs.empty())
	{
		copy(_newJobs.front()->list.begin(),_newJobs.front()->list.end(), ostream_iterator<string>(outFile,"\n"));
		temp.push(_newJobs.front());
		_newJobs.pop();
	}
	_batch.push(pair<string,queue<BatchJob*>>(username,temp));	
	outFile.close();
	return true;
}
//add user/date of execution
bool Inventory::generateLogFile(char *filename, string username){
	int size_1,size_2;
	using namespace System;
	DateTime^ temp = gcnew DateTime;
	temp = DateTime::Now;
	string now = Wrapper::toUnmanagedString(temp->ToString());
	ofstream outFile;
	outFile.open(filename,ios::app);
	if(outFile.fail()) return false;
	outFile<<"[Executed by <" + username + "> on <" + now +">]" << endl;
	size_1 = _log.size();
	for(int i = 0;i<size_1;i++){
		size_2 = _log.front().size();
		for(int j=0;j<size_2;j++){
			if(j!=0)
				outFile<<" ";
			outFile<<_log.front().front();
			_log.front().pop();

		}
		outFile<<endl;
		_log.pop();
	}
	outFile.close();
	delete temp;
	return true;
}
#pragma endregion
/********************************* END OF BATCH *********************************/
