#include "main.h"

using namespace std;

int main(void){

	/* Initialize menus */
	Menu *currentMenu = init_menus();

	/* Initialize inventory */
	Inventory inventory;
	if(!inventory.loadInventory("C:\\Users\\Ninja\\Desktop\\batchdata.txt")) currentMenu->printError(0);	
	if(!inventory.loadBatchfile("C:\\Users\\Ninja\\Desktop\\batchjobs.txt")) currentMenu->printError(0);

	char choice = '0';	

	while(choice != 'q'){
		currentMenu->printOptions();
		choice = currentMenu->getCmd();
		if (currentMenu->doCmd(choice) != NULL) (*(currentMenu->doCmd(choice)))(currentMenu,inventory,(int)choice-49);
		currentMenu = currentMenu->nextMenu(choice);
	}
	user_save_data(currentMenu,inventory,0);
	return 0;
}

/*** MENU SETTINGS ***/
Menu* init_menus(){
	/* Initialize menus */
	static Menu mainMenu(NULL, "MAIN MENU" );
	static Menu cashierMenu(&mainMenu, "CASHIER MENU");
	static Menu managerMenu(&mainMenu, "MANAGER MENU");
	static Menu statisticsMenu(&managerMenu, "PRODUCT STATISTICS");
	static Menu searchMenu(&managerMenu, "SEARCH BY:");
	/* Set options */
	mainMenu.setOption(&cashierMenu, "Log in as Cashier", NULL);
	mainMenu.setOption(&managerMenu, "Log in as Manager", NULL);	
	mainMenu.setOption(NULL, "Save Data", &user_save_data);
	cashierMenu.setOption(NULL, "Sell product", &user_sell_product);
	cashierMenu.setOption(NULL, "Restock product", &user_restock_product);
	managerMenu.setOption(NULL, "Add a new product", &user_add_product);
	managerMenu.setOption(NULL, "Remove an existing product", &user_delete_product);
	managerMenu.setOption(NULL, "Check product expiry", &user_check_expiry);
	managerMenu.setOption(&searchMenu, "Search for product(s)", NULL);
	managerMenu.setOption(NULL, "Reset sales for product", &user_reset_sales);
	managerMenu.setOption(&statisticsMenu, "Get product statistics", NULL);	
	managerMenu.setOption(NULL,"Execute batchjobs",&user_execute_batch);
	statisticsMenu.setOption(NULL, "Print overall top products", &locate_top_products);
	statisticsMenu.setOption(NULL, "Print best product for a category", &locate_best_product);
	statisticsMenu.setOption(NULL, "Get this month's best manufacturer", &locate_best_manufacturer);
	searchMenu.setOption(NULL, "Name", &user_search_product);
	searchMenu.setOption(NULL, "Barcode", &user_search_product);
	searchMenu.setOption(NULL, "Category", &user_search_product);
	searchMenu.setOption(NULL, "Manufacturer", &user_search_product);
	return &mainMenu;
}

/*** INVENTORY ACCESS ***/
void user_save_data(Menu* menu,Inventory &inv, int x){
	if(inv.saveInventory("data.txt") )
		menu->print("Inventory saved!");
	else
		menu->printError(2);
}
void user_add_product(Menu* menu, Inventory &inv,int){
	bool perishable;
	string name, category, barcode, manufacturer;
	unsigned int numstock, numsold, expiry;
	double price, discount;
	menu->getProductInfo(&perishable,&name,&category,&barcode,&manufacturer,&numstock,&numsold,&price,&expiry,&discount);
	if(perishable){
		PerishableProduct insert(name,category,barcode,manufacturer,price,numstock,numsold,expiry,discount);
		inv.addProduct(insert);
	}
	else{
		Product insert(name,category,barcode,manufacturer,price,numstock,numsold);
		inv.addProduct(insert);
	}
	return;
}
void user_delete_product(Menu* menu,Inventory &inv, int){
	string key = menu->getStr("barcode");
	if(!inv.deleteProduct(key)) menu->printError(1);
	else menu->printSuccess();
	return;
}
void user_sell_product(Menu* menu,Inventory &inv, int){	
	string key = menu->getStr("barcode");
	if(inv.findProduct(key) == NULL) menu->printError(1);
	else{
		int num = menu->getQty();
		if(!inv.sellProduct(key,num)) menu->printError(4);
		else menu->printSuccess();
	}
	return;
}
void user_restock_product(Menu* menu,Inventory &inv, int){
	string key = menu->getStr("barcode");
	if(inv.findProduct(key) == NULL) menu->printError(1);
	else {
		int num = menu->getQty();
		inv.restockProduct(key,num);
		menu->printSuccess();
	}
	return;
}
void user_reset_sales(Menu* menu,Inventory &inv, int){
	string key = menu->getStr("barcode");
	if (!inv.resetSalesCount(key)) menu->printError(1);
	else menu->printSuccess();
	return;
}
void user_check_expiry(Menu* menu,Inventory &inv, int){
	string key = menu->getStr("barcode");
	int expired = inv.checkProductExpiry(key);
	if(expired>0){
		char nchar[21];
		sprintf(nchar, "%d", expired);
		string numstr(nchar);
		menu->print(numstr+" days left to expiry!");
	}
	else if(expired == 0) menu->print("Product has expired!");
	else if(expired == -1) menu->print("Product is not perishable!");
	else menu->printError(1);
		return;
	}

/*** INVENTORY SEARCH ***/
void locate_best_manufacturer(Menu* menu,Inventory &inv, int){
	list<pair<string,double>> result;
	if(inv.findBestManufacturer(result)) menu->printList(result);
}

void locate_top_products(Menu* menu,Inventory &inv, int){
	int x = menu->getQty();
	list<pair<Product*,double>> products;
	if(inv.findTopProducts(products,NULL,x))	// get top X products
		menu->printList(products);			// print them!
	else menu->printError(3);
}

void locate_best_product(Menu* menu,Inventory &inv, int){
	string str = menu->getStr("category");
	list<Product*> list1;
	list<pair<Product*,double>> product;				// list containing the best product(s). may have tie.
	if(inv.searchProducts(list1,str,'c')){				// get all products of specified category
		inv.findTopProducts(product,&list1,1);			// find best product within it
		menu->printList(product);						// print it!
	}
	else menu->printError(3);
}

void user_search_product(Menu* menu,Inventory &inv, int x){
	list<Product*> products;
	bool success;
	switch(x){
		case 0:
			success = inv.searchProducts(products,menu->getStr("name"),'n'); break;
		case 1:		
			success = inv.searchProducts(products,menu->getStr("barcode"),'b'); break;
		case 2:	
			success = inv.searchProducts(products,menu->getStr("category"),'c'); break;
		case 3:
			success = inv.searchProducts(products,menu->getStr("manufacturer"),'m'); break;
		default:
			success = false; break;
	}	
	if(success) menu->printList(products);
	else menu->printError(3);
}
void user_execute_batch(Menu* menu,Inventory &inv,int)
{
	if(inv.executeBatch())
		menu->printSuccess();
	else
		menu->printError(2);
}