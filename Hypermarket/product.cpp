
#include "stdafx.h"
#include "product.h"

using namespace std;

// Constructors
Product::Product (	string name, string category, string barcode, string manufacturer,
					double price, unsigned int numstock, unsigned int numsold) :
					_name(name),
					_category(category),
					_barcode(barcode),
					_price(price),
					_manufacturer(manufacturer),
					_numstock(numstock),
					_numsold(numsold){}
PerishableProduct::PerishableProduct (string name, string category, string barcode, string manufacturer,
double price, unsigned int numstock, unsigned int numsold, unsigned int expiry, double discount) :
Product (name,category,barcode,manufacturer,price,numstock,numsold){
	_expirydate = expiry;
	_discount = discount;
}

// Cloners
Product* Product::clone() const {
	return new Product(*this);
}
Product* PerishableProduct::clone() const{
	return new PerishableProduct(*this);
}

// Getters
bool Product::isPerishable() {	return false; }
bool PerishableProduct::isPerishable() { return true; }
string Product::getName() const {	return _name; }
string Product::getCategory() const {	return _category; }
string Product::getBarcode() const { return _barcode; }
string Product::getManufacturer() const { return _manufacturer; }
double Product::getPrice() const { return _price; }
unsigned Product::getNumStock() const { return _numstock; }
unsigned Product::getNumSold() const { return _numsold; }

int Product::getExpiry() const { return 0; }
double Product::getDiscount() const { return 0; }
int PerishableProduct::getExpiry() const { return _expirydate; }
double PerishableProduct::getDiscount() const { return _discount; }


// Mutators
void Product::changePrice(double a) { _price = a; }
void Product::changeNumStock(unsigned int a) { _numstock = a; }
void Product::changeName(string a) { _name = a; }
void Product::changeCategory(string a) { _category = a; }
void Product::changeManufacturer(string a) { _manufacturer = a; }
void Product::resetNumSold() { _numsold = 0;}
void Product::changeDiscount(double a) {}
void PerishableProduct::changeDiscount(double a) {_discount = a;}
bool Product::sell(unsigned int a) {
	_numsold += a;
	_numstock -= a;
	if(a >= 0)
		return true;
	else {
		_numstock += a;
		_numsold -= a;
		return false;
	}
}