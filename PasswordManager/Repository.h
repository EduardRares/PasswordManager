#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Domain.h"

using namespace std;

class Repository
{
private:
	string filename;
	vector<Account> accounts;
public:
	Repository(string filename) : filename(filename) { loadFromFile(); }
	~Repository() = default;
	//add an account to the repository
	void addAccount(Account acc) { accounts.push_back(acc); }
	//remove an account from the repository
	void removeAccount(string domain);
	//update an account from the repository
	void updateAccount(string domain, string username, string password);
	//get all accounts from the repository
	vector<Account> getAllAccounts() { return accounts; }
	//save the accounts to the file
	void saveToFile();
	//load the accounts from the file
	void loadFromFile();
};

#endif // !REPOSITORY_H

