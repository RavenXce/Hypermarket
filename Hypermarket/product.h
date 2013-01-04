#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

public class Product
{
private:
	string _name;
	string _category;
	string _barcode;
	string _manufacturer;
	double _price;	
	unsigned int _numstock;
	unsigned int _numsold;

public:
	Product(string name = "", string category = "", string barcode = "", string manufacturer = "",
					double price = 0, unsigned int numstock = 0 , unsigned int numsold = 0);
	virtual Product* clone() const;
	virtual bool isPerishable();
	string getName() const;
	string getCategory() const;
	string getBarcode() const;	
	string getManufacturer() const;
	double getPrice() const;
	unsigned int getNumStock() const;
	unsigned int getNumSold() const;
	virtual int getExpiry() const;
	virtual double getDiscount() const;
	virtual void changeDiscount(double);
	void changeName(string);
	void changeCategory(string);
	void changeManufacturer(string);
	void changePrice(double);
	void changeNumStock(unsigned int);
	void resetNumSold();
	bool sell(unsigned int);
};

class PerishableProduct : public Product {

	int _expirydate;
	double _discount;
public:
	PerishableProduct (string name = "", string category = "", string barcode = "", string manufacturer = "",
					double price = 0, unsigned int numstock = 0 , unsigned int numsold = 0, unsigned int = 0, double = 0);
	Product* clone() const;
	bool isPerishable();
	int getExpiry() const;
	double getDiscount() const;
	void changeDiscount(double);
};

#endif