#pragma once
#include <string>
#include "User.h"
using namespace std;

User::User(const string _login, const string _password, const string _name)	//�������� ����������� 
{
	login = _login;
	password = _password;
	name = _name; 
}

const string& User::getUserLogin () const //������� ����� ������������
{ 
	return login; 
} 

const string& User::getUserPassword() const	//������� ������ ������������ 
{
	return password;
}

const string& User::getUserName() const	//������� ��� ������������ 
{
	return name;
}