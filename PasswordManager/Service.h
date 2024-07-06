#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include "Repository.h"
#include "Domain.h"
#include <time.h>

using namespace std;

class Service
{
private:
	Repository* repo;
public:
	Service(Repository* repo) : repo(repo) {}
	~Service() = default;
	//add an account to the repository
	void addAccount(string domain, string username, string password);
	//remove an account from the repository
	void removeAccount(string domain);
	//update an account from the repository
	void updateAccount(string domain, string username, string password);
	//get all accounts from the repository
	vector<Account> getAllAccounts() { return repo->getAllAccounts(); }
	//get all accounts from the repository with a specific domain
	vector<Account> getSpecificAccounts(const string& domain);
	//check if a string is a substring of another string
	bool isSubstring(const string& str, const string& substring);
	string passwordGenerator();
};
#endif // !SERVICE_H

