#include "stdafx.h"
#include "password.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Password::Password () {}

bool Password::load_pw_data (char* filename) {
	ifstream inFile(filename);
	string username, password;
	int size,level;
	if(inFile.fail()) return false;
	inFile >> size;
	accounts.clear();
	for (int i=0; i<size; i++) {
		inFile >> level >> username >> password;
		account newaccount = {level,username,password};
		accounts.push_back(newaccount);
	}
	inFile.close();
	return true;
}

bool Password::save_pw_data (char* filename) {
	ofstream outFile(filename);
	if(outFile.fail()) return false;
	outFile << accounts.size() << endl;
	for(int i=accounts.size()-1; i>=0; i--) {
		outFile << accounts[i].access_level << " " << accounts[i].userID << " " << accounts[i].password << endl;
	}
	return true;
	outFile.close();
}

bool Password::add_account (int level, string username, string password) {
	encrypt_password (password,level);
	if(find_account(username)) return false; // duplicate user
	account newaccount = {level,username,password};
	accounts.push_back(newaccount);
	return true;
}

bool Password::delete_account (string username){
	for(int i=accounts.size()-1; i>=0; i--){
		if (accounts[i].userID==username){
			accounts.erase(accounts.begin()+i);
			return true;
		}
	}
	return false;
}

vector<pair<int,string>> Password::get_accounts(){
	vector<pair<int,string>> ret;
	for(int i=0; i < accounts.size(); i++)
		ret.push_back(make_pair(accounts[i].access_level,accounts[i].userID));
	return ret;
}

void Password::encrypt_password(string& password, char level) {
	int bytes_to_encrypt=128, size=128, S[128], keystream[128], i, j=0;
	string key=password+level+"Wiki";				// RC4 encryption algorithm
	for (i=0; i<size; i++) S[i]=i;					// identity permutation
	for (i=0; i<size; i++) {						// KSA
		j=(j+S[i]+key[i%key.size()])%size;
		swap(S[i], S[j]);
	}
	i=0; j=0;
	while (bytes_to_encrypt--) {					// PRNGA
		i=(i+1)%size;
		j=(j+S[i])%size;
		swap(S[i], S[j]);
		keystream[i]=S[(S[i]+S[j])%size];
	}
	for(int i = 0; i<password.size(); i++) {		// XOR
		password[i]=password[i]^keystream[i];
		//cout << hex << (int)password[i];
	}
	password=convert_to_hex(password);
}

string Password::convert_to_hex(string password) {
	ostringstream os;
	for (int i=0; i<password.size(); i++) os << hex << uppercase << (int)password[i];
	return os.str();
}

void Password::swap(int& a, int& b) {
	int temp=a;
	a=b;
	b=temp;
}

bool Password::find_account (string username) {
	for(int i=accounts.size()-1; i>=0; i--)
		if (accounts[i].userID==username) return true;
	return false;
}

bool Password::log_in (int level, string username, string password) {	
	for(int i=accounts.size()-1; i>=0; i--){
		if (accounts[i].access_level>=level && accounts[i].userID==username){
			encrypt_password(password,accounts[i].access_level);
				if(accounts[i].password==password)
					return true;
				else
					return false;
		}
	}
	return false;
}

bool Password::has_access (int level, string username) {
	for(int i=accounts.size()-1; i>=0; i--){
		if (accounts[i].userID==username){
			if(accounts[i].access_level >= level)
				return true;
			else return false;
		}
	}
	return false;
}
