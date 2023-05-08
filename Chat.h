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

struct UserLoginExp : public std::exception	//Исключения
{
	const char* what() const noexcept override { return "ошибка: логин пользователя занят"; } 
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "ошибка: имя пользователя занято"; }
};

class Chat
{
public:
	void start();	// запуск чата
	bool isChatWork() const { return isChatWork_; } // проверка, работает чат или нет (если true - чат работает, если false - нет) 
	void showLoginMenu(); // Отображение стартового меню программы
	User* getCurrentUser() const { return currentUser_; }
	void showUserMenu(); // отображает внутреннее меню чата, после авторизации пользователя
	int hash_func(string pass_name); //Хеш функция методом умножения, возвращает хеш от 100
    bool login_func(string _login, string _pass);    //проверка совпадения логина и хеша

private:
	bool isChatWork_ = false; // Флаг для выхода из меню 
	void login();	// Авторизация в чат по созданному логину и паролю
	void signUp();	// Регистрация пользователя в чате 
	User* getUserByLogin(const std::string& login) const;

	User* getUserByName(const std::string& name);
	User* currentUser_ = nullptr;	// показывает текущего пользователя 
	std::vector<User> users_;		// Динамический массив (вектор) текущих пользователей 
	std::vector<Message> messages_; // Динамический массив (вектор) сообщений
	void showChat() const; // показывает отправленные сообщения, конкретному пользователю или всем
	void showAllUsersName() const;	// Показывает имена пользователей чата
	void addMessage(); //Создание сообщения

    struct AuthData //структура данных отвечающая за данные для аутентификации
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
            //strcpy(login, _login);//сторочка ниже замена этой
            login.append(_login);
            pass_hash_func = sh1;
        }
        AuthData& operator = (const AuthData& other)
        {
            //strcpy(login, other.login);//сторочка ниже замена этой
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