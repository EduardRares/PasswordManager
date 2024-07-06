#include "Service.h"

void Service::addAccount(string domain, string username, string password)
{
	if (!isSubstring(domain, "https://")) {
		domain = "https://" + domain;
	}
	Account acc = Account(domain, username, password);
	repo->addAccount(acc);
	repo->saveToFile();
}

void Service::removeAccount(string domain)
{
	repo->removeAccount(domain);
}

void Service::updateAccount(string domain, string username, string password)
{
	repo->updateAccount(domain, username, password);
}

vector<Account> Service::getSpecificAccounts(const string& domain)
{
	vector<Account> acc = repo->getAllAccounts();
	vector<Account> aux;
	for (auto& el : acc) {
		if (isSubstring(el.getDomain(), domain)) aux.push_back(el);
	}
	return aux;
}

bool Service::isSubstring(const string& str, const string& substring)
{
	if (str.find(substring) != std::string::npos) {
		return true;
	}
	else {
		return false;
	}
}

string Service::passwordGenerator()
{
	string password = "";
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		int r = rand() % 3;
		if (r == 0)
			password += 'a' + rand() % 26;
		else if (r == 1)
			password += 'A' + rand() % 26;
		else
			password += '0' + rand() % 10;
	}
	return password;
}
