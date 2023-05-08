#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
//#include "HashTable.h"
//typedef unsigned int uint;
#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5
using namespace std;

struct UserLoginExp : public std::exception	//����������
{
	const char* what() const noexcept override { return "������: ����� ������������ �����"; } 
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "������: ��� ������������ ������"; }
};

class Chat
{
public:
	void start();	// ������ ����
	bool isChatWork() const { return isChatWork_; } // ��������, �������� ��� ��� ��� (���� true - ��� ��������, ���� false - ���) 
	void showLoginMenu(); // ����������� ���������� ���� ���������
	User* getCurrentUser() const { return currentUser_; }
	void showUserMenu(); // ���������� ���������� ���� ����, ����� ����������� ������������
	int hash_func(string pass_name); //��� ������� ������� ���������, ���������� ��� �� 100
    bool login_func(string _login, string _pass);    //�������� ���������� ������ � ����

private:
	bool isChatWork_ = false; // ���� ��� ������ �� ���� 
	void login();	// ����������� � ��� �� ���������� ������ � ������
	void signUp();	// ����������� ������������ � ���� 
	User* getUserByLogin(const std::string& login) const;

	User* getUserByName(const std::string& name);
	User* currentUser_ = nullptr;	// ���������� �������� ������������ 
	std::vector<User> users_;		// ������������ ������ (������) ������� ������������� 
	std::vector<Message> messages_; // ������������ ������ (������) ���������
	void showChat() const; // ���������� ������������ ���������, ����������� ������������ ��� ����
	void showAllUsersName() const;	// ���������� ����� ������������� ����
	void addMessage(); //�������� ���������

    struct AuthData //��������� ������ ���������� �� ������ ��� ��������������
    {
        AuthData() :
            login(""),
            pass_hash_func(0)
        {}
        ~AuthData() 
        {
            if (pass_hash_func != 0)
                delete[] pass_hash_func;
        }
        AuthData(string _login, int* sh1)
        {
            //strcpy(login, _login);//�������� ���� ������ ����
            login.append(_login);
            pass_hash_func = sh1;
        }
        AuthData& operator = (const AuthData& other)
        {
            //strcpy(login, other.login);//�������� ���� ������ ����
            login.append(other.login);

            if (pass_hash_func != 0)
                delete[] pass_hash_func;
            pass_hash_func = new int[SHA1HASHLENGTHUINTS];

            memcpy(pass_hash_func, other.pass_hash_func, SHA1HASHLENGTHBYTES);

            return *this;
        }
        string login;
        int* pass_hash_func;
    };
    AuthData data[100];
    int data_count = 0;
};