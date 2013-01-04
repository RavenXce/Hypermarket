#ifndef INVEN_H
#define INVEN_H

#define BARCODE 0x01
#define NAME 0x02
#define CATEGORY 0x04
#define MANUFACTURER 0x08

#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "batchjob.h"
#include "date.h"
#include "product.h"

using namespace std;

class Inventory {
private:
	map<string,Product*> _inv;
	stack<pair<string,queue<BatchJob*>>> _batch; //username, batchjobs pair
	queue<queue<string>> _log;	
	queue<BatchJob*> _newJobs;
	bool strmatch(string,string,bool);
	bool _loaded;
	bool _saved;
public:
	Inventory();
	bool isSaved();
	bool isLoaded();
	bool batchLoaded();
	void unloadInventory();
	bool loadInventory(char*);
	bool saveInventory(char*);
	bool loadBatchfile(char*);
	bool executeBatch(char*,string);	
	bool generateLogFile(char*,string);	
	bool addBatchJob(const string &, const string &);
	bool addNewJob(BatchJob*);	
	void productModified();
	bool addProduct(Product&);
	bool deleteProduct(string);	
	bool sellProduct(string,unsigned int);
	bool restockProduct(string,unsigned int);
	bool resetSalesCount(string);
	int checkProductExpiry(string); //deprecated
	Product* findProduct(string); //deprecated
	bool findBestManufacturer(vector<pair<string,double>>& outputList, const vector<Product*> *searchlist, int num);
	bool findTopProducts(vector<pair<Product*,double>>& outputList, const vector<Product*> *searchList, int num);
	bool searchProducts(vector<Product*>& outputList, string matchStr, char type, bool exact);
};

#endif