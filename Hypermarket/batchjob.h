#ifndef BatchJob_H
#define BatchJob_H

#include <queue>
#include <string>
#include <map>
#include "date.h"
#include "product.h"

class BatchJob{
protected:
	string _code;
	string _barcode;
public:
	vector<string> list;
	BatchJob(string code = "",string barcode = "");
	virtual void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &) = 0;
};

class BatchJobAdd:public BatchJob{
private:
	string _name;
	string _category;
	string _price;
	string _manufacturer;
	string _numstock;
public:
	BatchJobAdd(string code = "",string barcode = "", string name = "",string category = "", string price = "", string manufacturer = "", string numstock = "");
	void execute(map<string,Product*>& ,queue<queue<string>>& ,const string &);
};

class BatchJobDelete:public BatchJob{

public:
	BatchJobDelete(string code = "",string barcode = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobRestock:public BatchJob{
private:
	string _numadd;
public:
	BatchJobRestock(string code = "",string barcode = "",string numadd = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobDispose:public BatchJob{
private:
	string _curdate;
public:
	BatchJobDispose(string code = "",string barcode = "", string curdate = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};
class BatchJobDisposeAll:public BatchJob{

	string _curdate;
public:
	BatchJobDisposeAll(string code = "",string curdate = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};
class BatchJobSale:public BatchJob{
private:
	string _numsold;
public:
	BatchJobSale(string code = "",string barcode = "",string numsold = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobDiscount:public BatchJob{
private:
	string _days;
	string _discount;
public:
	BatchJobDiscount(string code = "",string days = "", string discount = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobRestockManufacturer:public BatchJob{
private:
	string _numadd;
	string _manufacturer;
public:
	BatchJobRestockManufacturer(string code = "",string manufacturer = "",string numadd = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobRestockCategory:public BatchJob{
private:
	string _numadd;
	string _category;
public:
	BatchJobRestockCategory(string code = "",string category = "",string numadd = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};

class BatchJobRestockLeft:public BatchJob{
private:
	string _numadd;
	string _numleft;
public:
	BatchJobRestockLeft(string code = "", string numleft = "",string numadd = "");
	void execute(map<string,Product*>& ,queue<queue<string>>&  ,const string &);
};
#endif