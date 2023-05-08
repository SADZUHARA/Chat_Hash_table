#pragma once
#include <string>
using namespace std;


class User
{
public:
	User(const string _login, const string _password, const string _name);

	const string& getUserLogin() const;
	const string& getUserPassword() const;
	const string& getUserName() const;

private:
	string login;	// логин пользователя
	string password;// пароль пользователя
	string name;	// имя пользователя

};
