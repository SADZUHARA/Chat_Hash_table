#pragma once
#include <string>
#include "User.h"
using namespace std;

User::User(const string _login, const string _password, const string _name)	//создание пользоватля 
{
	login = _login;
	password = _password;
	name = _name; 
}

const string& User::getUserLogin () const //вернуть логин пользователя
{ 
	return login; 
} 

const string& User::getUserPassword() const	//вернуть пароль пользователя 
{
	return password;
}

const string& User::getUserName() const	//вернуть имя пользователя 
{
	return name;
}