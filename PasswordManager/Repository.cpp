#include "Repository.h"

void Repository::removeAccount(string domain)
{
	auto it = find_if(accounts.begin(), accounts.end(), [domain](Account acc) {return acc.getDomain() == domain; });
	if (it != accounts.end())
		accounts.erase(it);
	saveToFile();
}

void Repository::updateAccount(string domain, string username, string password)
{
	auto it = find_if(accounts.begin(), accounts.end(), [domain](Account acc) {return acc.getDomain() == domain; });
	if (it != accounts.end())
	{
		Account acc = *it;
		acc = Account(domain, username, password);
	}
	saveToFile();
}

void Repository::saveToFile()
{
	ofstream f(filename);
	for (auto acc : accounts)
		f << acc.getDomain() << "," << acc.getUsername() << "," << acc.getPassword() << "\n";
	f.close();
}

void Repository::loadFromFile()
{
	ifstream f(filename);
	string domain, username, password;
	string line;
	while (getline(f, line))
	{
		stringstream ss(line);
		getline(ss, domain, ',');
		getline(ss, username, ',');
		getline(ss, password, ',');
		Account acc = Account(domain, username, password);
		accounts.push_back(acc);
	}
	f.close();
}
