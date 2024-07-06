#ifndef DOMAIN_H
#define DOMAIN_H

#include <iostream>
#include <string>

using namespace std;

class Account
{
public:
	Account(string domain, string username, string password) : domain(domain), username(username), password(password) {}
	~Account() = default;

	string getDomain() const { return domain; }
	string getUsername() const { return username; }
	string getPassword() const { return password; }
private: 	
	string domain;
	string username;
	string password;

};
#endif // !DOMAIN_H