#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "menu.h"

Menu *init_menus();
void user_add_product(Menu*,Inventory&,int); // requirement 1
void user_delete_product(Menu*,Inventory&,int); //2
void user_restock_product(Inventory&,int); //5
void user_reset_sales(Menu*,Inventory&,int); //3
void user_check_expiry(Menu*,Inventory&,int); //9
void user_sell_product(Menu*,Inventory&,int); //4
void user_save_data(Menu*,Inventory&,int);
void user_search_product(Menu*,Inventory&,int);
void user_execute_batch(Menu*,Inventory&,int);
void locate_top_products(Menu*,Inventory&,int); //6
void locate_best_product(Menu*,Inventory&,int); //7
void locate_best_manufacturer(Menu*,Inventory&,int);//8

#endif