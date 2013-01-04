#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "inventory.h"

using namespace std;

public class Menu{	
typedef void (*funcptr)(Menu*,Inventory&,int);
private:
	string subheader;
	struct option {
		string text;
		Menu* leaf;
		funcptr function;
	};
	vector<option> options;
	Menu *prev_menu;
	void printHeader();
public:
	Menu(Menu* = NULL, string subheader = "");
	Menu *nextMenu(char);
	funcptr doCmd(char);
	char getCmd();
	int getQty();
	string getStr(string);
	void setOption(Menu*,string,funcptr);
	void printSuccess();
	void printOptions();
	void printError(int);
	void printProduct(Product&);
	void printList(list<Product*>);
	void printList(list<pair<string,double>>);
	void printList(list<pair<Product*,double> >);
	bool getProductInfo(bool *perishable,string *name,string *category,string *barcode,string *manufacturer,unsigned int *numstock,unsigned int *numsold, double *price,unsigned int *expiry, double *discount);
	template <typename T> void print(T str){ cout << " " << str; getchar(); }
};

/* External Inventory Access Functions (in main) */
extern void user_add_product(Menu*,Inventory&,int);
extern void user_delete_product(Menu*,Inventory&,int);
extern void user_sell_product(Menu*,Inventory&,int);
extern void user_restock_product(Menu*,Inventory&,int);
extern void user_reset_sales(Menu*,Inventory&,int);
extern void user_check_expiry(Menu*,Inventory&,int);
extern void user_save_data(Menu*,Inventory&,int);
extern void user_search_product(Menu*,Inventory&,int);
extern void user_execute_batch(Menu*,Inventory&,int);
extern void locate_top_products(Menu*,Inventory&,int);
extern void locate_best_product(Menu*,Inventory&,int);
extern void locate_best_manufacturer(Menu*,Inventory&,int);

#endif