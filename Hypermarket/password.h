#ifndef PASSWORD_H
#define PASSWORD_H
#include <vector>
using namespace std;

class Password {
private:
	struct account{
		int access_level;
		string userID;
		string password;
	};
	vector<account> accounts;	
	bool find_account (string username);
	void encrypt_password (string& password,char type);
	string convert_to_hex (string password);
	void swap(int& a, int& b);	
public:
	Password ();
	vector<pair<int,string>> get_accounts();
	bool load_pw_data (char *);
	bool save_pw_data (char *);
	bool add_account (int level, string username, string password);
	bool delete_account (string username);
	bool log_in(int level, string username, string password);
	bool has_access (int level, string username);
};

#endif PASSWORD_H