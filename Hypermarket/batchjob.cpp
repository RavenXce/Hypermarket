#include "stdafx.h"
#include "batchjob.h"

BatchJob::BatchJob(string code,string barcode):_code(code),_barcode(barcode)
{
}
BatchJobAdd::BatchJobAdd(string code,string barcode, string name,string category , string price , string manufacturer , string numstock ):BatchJob(code,barcode)
{
	_name = name;
	_category = category;
	_price = price;
	_manufacturer = manufacturer;
	_numstock = numstock;
	list.push_back(code);
	list.push_back(barcode);
	list.push_back(name);
	list.push_back(category);
	list.push_back(price);
	list.push_back(manufacturer);
	list.push_back(numstock);
}
BatchJobDelete::BatchJobDelete(string code ,string barcode ):BatchJob(code,barcode)
{
	list.push_back(code);
	list.push_back(barcode);
}
BatchJobRestock::BatchJobRestock(string code ,string barcode ,string numadd ):BatchJob(code,barcode)
{
	_numadd = numadd;
	list.push_back(code);
	list.push_back(barcode);
	list.push_back(numadd);
}
BatchJobDispose::BatchJobDispose(string code ,string barcode , string curdate ):BatchJob(code,barcode)
{
	_curdate = curdate;
	list.push_back(code);
	list.push_back(barcode);
	list.push_back(curdate);
}
BatchJobDisposeAll::BatchJobDisposeAll(string code ,string curdate)
{
	_code = code;
	_curdate = curdate;
	list.push_back(code);
	list.push_back(curdate);
}
BatchJobRestockManufacturer::BatchJobRestockManufacturer(string code,string manufacturer ,string numadd)
{
	_code = code;
	_manufacturer = manufacturer;
	_numadd = numadd;
	list.push_back(code);
	list.push_back(manufacturer);
	list.push_back(numadd);
}
BatchJobRestockCategory::BatchJobRestockCategory(string code, string category ,string numadd)
{
	_code = code;
	_category = category;
	_numadd = numadd;
	list.push_back(code);
	list.push_back(category);
	list.push_back(numadd);
}
BatchJobRestockLeft::BatchJobRestockLeft(string code, string numleft ,string numadd)
{
	_code = code;
	_numleft = numleft;
	_numadd = numadd;
	list.push_back(code);
	list.push_back(numleft);
	list.push_back(numadd);
}
BatchJobSale::BatchJobSale(string code ,string barcode ,string numsold ):BatchJob(code,barcode)
{
	_numsold = numsold;
	list.push_back(code);
	list.push_back(barcode);
	list.push_back(numsold);
}
BatchJobDiscount::BatchJobDiscount(string code  ,string days, string discount)
{
	_code = code;
	_days = days;
	_discount = discount;
	list.push_back(code);
	list.push_back(days);
	list.push_back(discount);
}
void BatchJobAdd::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	Product insert(_name,_category,_barcode,_manufacturer,atof(_price.c_str()),atoi(_numstock.c_str()));
	Product *product = insert.clone();
	if(_map.find(insert.getBarcode())==_map.end())
	{
		_map.insert(make_pair(insert.getBarcode(),product));
	}
	else
	{
		queue<string> temp;
		temp.push(_barcode);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}

void BatchJobDelete::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	if(_map.find(_barcode)!=_map.end()){
		_map.erase(_map.find(_barcode));
	}
	else
	{
		queue<string> temp;
		temp.push(_barcode);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}

void BatchJobRestock::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	Product* product;
	if(_map.find(_barcode)!=_map.end()){
		product = _map.find(_barcode)->second;
		product->changeNumStock(atoi(_numadd.c_str()));
	}
	else
	{
		queue<string> temp;
		temp.push(_barcode);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}

void BatchJobDispose::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	Product *product;
	if(_map.find(_barcode)!=_map.end()){
		product = _map.find(_barcode)->second;
	}
	else
		product = NULL;

	if(product == NULL || (!product->isPerishable()) )
	{
		queue<string> temp;
		temp.push(_barcode);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
	else
	{
		string curTime;
		Date cur(atoi(_curdate.c_str()));
		Date exp(product->getExpiry());
		if(exp-cur > 0)
		{
			queue<string> temp;
			temp.push(_barcode);
			temp.push(_code);
			temp.push(username);
			_log.push(temp);
		}
		else
		{
			product->changeNumStock(0);
		}
	}
}

void BatchJobSale::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	Product* product;
	if(_map.find(_barcode)!=_map.end()){
		product = _map.find(_barcode)->second;
	}
	else
		product = NULL;

	if(product!=NULL && product->getNumStock() >= atoi(_numsold.c_str())){
		product->sell(atoi(_numsold.c_str()));
	}
	else
	{
		queue<string> temp;
		temp.push(_barcode);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}
void BatchJobDiscount::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	map<string,Product*>::iterator iter = _map.begin();
	for (  ; iter != _map.end() ; iter++)
	{
		if(iter->second->isPerishable())
		{
			string curTime;
			Date cur;
			Date exp(iter->second->getExpiry());
			if(exp - cur < atoi(_days.c_str()))
			{
				iter->second->changeDiscount(atof(_discount.c_str()));
			}
		}
	}

}
void BatchJobDisposeAll::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	map<string,Product*>::iterator iter = _map.begin();
	for (  ; iter != _map.end() ; iter++)
	{
		if(iter->second->isPerishable())
		{
			string curTime;
			Date cur(atoi(_curdate.c_str()));
			Date exp(iter->second->getExpiry());
			if(exp - cur <= 0)
			{
				iter->second->changeNumStock(0);
			}
		}
	}
}
void BatchJobRestockManufacturer::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	bool mask = false;
	map<string,Product*>::iterator iter = _map.begin();
	for (  ; iter != _map.end() ; iter++)
	{
		if(iter->second->getManufacturer() == _manufacturer)
		{
			mask = true;
			iter->second->changeNumStock(atoi(_numadd.c_str()));
		}
	}
	if(!mask)
	{
		queue<string> temp;
		temp.push(_manufacturer);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}
void BatchJobRestockCategory::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	bool mask = false;
	map<string,Product*>::iterator iter = _map.begin();
	for (  ; iter != _map.end() ; iter++)
	{
		if(iter->second->getCategory() == _category)
		{
			mask = true;
			iter->second->changeNumStock(atoi(_numadd.c_str()));
		}
	}
	if(!mask)
	{
		queue<string> temp;
		temp.push(_category);
		temp.push(_code);
		temp.push(username);
		_log.push(temp);
	}
}
void BatchJobRestockLeft::execute(map<string,Product*>& _map,queue<queue<string>>& _log,const string& username)
{
	map<string,Product*>::iterator iter = _map.begin();
	for (  ; iter != _map.end() ; iter++)
	{
		if(iter->second->getNumStock() < atoi(_numadd.c_str()))
		{
			iter->second->changeNumStock(atoi(_numadd.c_str()));
		}
	}
}