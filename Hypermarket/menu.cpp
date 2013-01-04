#include "stdafx.h"
#include "menu.h"
#include <Windows.h>
using namespace std;
typedef void (*funcptr)(Menu*,Inventory&,int);

Menu::Menu(Menu * prev,string header):prev_menu(prev),subheader(header){}

/* Print functions */
void Menu::printHeader(){
	system("cls");
	system("Color F0");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	TCHAR szNewTitle[MAX_PATH] = TEXT("CEG ICMS");
	SetConsoleTitle(szNewTitle);
	GetConsoleScreenBufferInfo(handle,&info);
	SetConsoleTextAttribute(handle,FOREGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << setw(info.dwSize.X) << setfill('-') << "" << endl;
	cout << "            CEG Hypermarket Inventory Control and Monitoring System             " << endl;
	cout << setw(info.dwSize.X) << setfill('-') << "" << endl;
	SetConsoleTextAttribute(handle,FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << " " << subheader << endl;
	cout << " " << setw(subheader.length()) << setfill('=') << "" << endl;
}

void Menu::printOptions(){
	printHeader();
	int i;
	for(i = 0; i < options.size(); i++)
		cout << " " << i+1 << ": " << options[i].text << endl;
	if(this->prev_menu != NULL) cout << " R: Return to previous menu" << endl; // don't print for main menu
	cout << " Q: Quit" << endl << endl << " ";
}

void Menu::printError(int type){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << " ";
	switch(type){
	case 0:
		cout << "ERROR! Failed to load file!"; break;
	case 1:
		cout << "ERROR! Product not found!"; break;
	case 2:
		cout << "ERROR! Failed to save to file!"; break;
	case 3:
		cout << "No matching products found!"; break;
	case 4:
		cout << "Not enough products to sell!"; break;
	case 5:
		cout << "ERROR! Invalid option..!"; break;
	default: break;
	}
	SetConsoleTextAttribute(handle,FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	getchar();
	return;
}
// TODO: merge "press enter continue?"
void Menu::printSuccess(){	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,0x0009 | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	cout << " Operation successful!";
	SetConsoleTextAttribute(handle,FOREGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	getchar();
}

void Menu::printProduct(Product& product){
	cout << endl;
	cout << " Name\t\t: " << product.getName() << endl;
	cout << " Category\t: " <<  product.getCategory() << endl;
	cout << " Barcode\t: " << product.getBarcode() << endl;	
	cout << " Manufacturer\t: " << product.getManufacturer() << endl;
	cout << " Price\t\t: $" << setiosflags(ios::fixed) << setprecision(2) << product.getPrice()  << endl;
	cout << " Stock left\t: " << product.getNumStock() << endl;
	cout << " Stock sold\t: " << product.getNumSold()  << endl;
	if(product.isPerishable()){
		cout << " Expiry\t\t: " << Date(product.getExpiry()).formatted()  << endl;
		cout << " Discount\t: " << product.getDiscount() << "%" << endl;
	}
	cout << endl;
}

void Menu::printList(list<pair<string,double>> manufacturers){
	list<pair<string,double>>::iterator it;
	cout << " Best manufacturer is:\t " << manufacturers.front().first << endl;
	if(manufacturers.size() > 1)
		for(it = manufacturers.begin(); it != manufacturers.end(); it++)
			cout << "\t\t\t " << it->first << endl;
	cout << " Revenue is:\t\t $" << setiosflags(ios::fixed) << setprecision(2) << manufacturers.front().second;
	getchar();
}
void Menu::printList(list<Product*> products){
	list<Product*>::iterator it;
	int i = 1;
	printHeader();
	cout << endl;
	for(it = products.begin(); it != products.end(); it++){
		cout << " #" << i << ": " << endl;
		cout << " ---";
		printProduct(**it);
		i++;
	}
	cout << " Press enter to continue...";
	getchar();
}
void Menu::printList(list<pair<Product*,double>> products){
	list<pair<Product*,double>>::iterator it;
	int i = 1;
	printHeader();
	cout << endl;
	for(it = products.begin(); it != products.end(); it++){
		cout << " RANK " << i << " " << endl;
		cout << " " << setw(7) << setfill('-') << " " << endl;
		cout << " Revenue\t: $" << setiosflags(ios::fixed) << setprecision(2) << it->second;
		printProduct(*(it->first));
		i++;
	}
	cout << " Press enter to continue...";
	getchar();
}

/* Execute functions */
funcptr Menu::doCmd(char choice){
	if((int)choice-49 < options.size())				// if number is valid
		return options[(int)choice-49].function;	// call it!
	else return NULL;								// else signify that it is invalid
}

void Menu::setOption(Menu* ptr, string text, funcptr callFunc){
	Menu::option temp;
	temp.function = callFunc;
	temp.text = text;
	temp.leaf = ptr;
	options.push_back(temp);
}

Menu * Menu::nextMenu(char choice){
	if(choice == 'r'){
		if(prev_menu!=NULL)
			return prev_menu; // return previous menu
	}
	else if(choice == 'q'){
		cout << " Exiting..." << endl;
		return this;
	}
	if((int)choice-49 < options.size())
		if (options[(int)choice-49].leaf == NULL) return this;
		else return options[(int)choice-49].leaf;	// return next menu
	else {
		printError(5);
		return this;		// if invalid number, do nothing.
	}
}

/* Input functions */
char Menu::getCmd(){
	char choice = '0';
	cin >> choice;
	getchar();
	cout << endl;
	return tolower(choice);
}

string Menu::getStr(string type){
	string str;
	printHeader();
	cout << " Please enter product " << type << ": ";
	getline(cin,str);
	return str;
}

int Menu::getQty(){
	int num;
	printHeader();
	cout << " Please enter quantity: ";
	cin >> num;
	getchar();
	return num;
}

bool Menu::getProductInfo(bool *perishable,string *name,string *category,string *barcode,string *manufacturer,unsigned int *numstock,unsigned int *numsold, double *price,unsigned int *expiry, double *discount){
	char in;
	printHeader();
	cout << " Please enter the following product information" << endl << endl;
	cout << " Name: ";
	getline(cin,*name);
	cout << " Category: ";
	getline(cin,*category);
	cout << " Barcode: ";
	cin >> *barcode;
	getchar();
	cout << " Manufacturer: ";
	getline(cin,*manufacturer);
	cout << " Price: $";
	cin >> *price;
	cout << " Stock: ";
	cin >> *numstock;
	/*
	getline(cin,*name);
	cout << " Please enter product category: ";
	getline(cin,*category);
	cout << " Please enter product barcode: ";
	cin >> *barcode;
	getchar();
	cout << " Please enter product manufacturer: ";
	getline(cin,*manufacturer);
	cout << " Please enter product price: ";
	cin >> *price;
	cout << " Please enter product stock: ";
	cin >> *numstock;*/
	*numsold = 0;
	while(1){
		printHeader();
		cout << " Is product a perishable good? Y/N: ";
		cin >> in;
		in = tolower(in);
		if(in == 'y'){
			*perishable = true;
			cout << endl << " Please input product expiry date: ";
			cin >> *expiry;
			cout << endl << " Please input product discount: ";
			cin >> *discount;
			break;
		}
		else if (in != 'n'){
			cout << " Invalid response!" << endl;
			getchar(); getchar();
		}
		else{
			*perishable = false;
			break;
		}
	}
	Product* tempProduct;
	if(*perishable)
		tempProduct = new PerishableProduct(*name,*category,*barcode,*manufacturer,*price,*numstock,*numsold,*expiry,*discount);
	else
		tempProduct = new Product (*name,*category,*barcode,*manufacturer,*price,*numstock,*numsold);
	printHeader();
	cout << " Confirm enter following product into inventory?" << endl;
	printProduct(*tempProduct);
	cout << " Y/N?: ";
	while(1){
		cin >> in;
		in = tolower(in);
		getchar();
		if (in == 'y'){
			delete tempProduct;
			return true;
		}
		else if (in != 'n')	{
			cout << " Invalid response!" << endl << " ";
			getchar();
		}
		else{
			cout << " Operation cancelled!" << endl << " ";
			getchar();
			return false;
		}
	}
}