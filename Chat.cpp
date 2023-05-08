#include <iostream>
#include "Chat.h"

void Chat::start() 
{
	isChatWork_ = true; // ���� ��� ������ �� ����	
}


void Chat::showLoginMenu() // ����������� ���������� ���� ��������� 
{
	currentUser_ = nullptr;	

	char i;

	do
	{
		cout << "" << endl;
		cout << "�������� �����, ��������������� ������" << endl;
		cout << "1 - �����������" << endl;
		cout << "2 - ����" << endl;
		cout << "0 - �����" << endl;
		cin >> i;

		switch (i)
		{
		case '1':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case '2':
			login();
			break;

		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "����� ����������� ������, ��������� ���� �����" << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // ���������� ���������� ���� ����, ����� ����������� ������������
{
	char i;

	cout << "������, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "1 - �������� ��������� " << endl;
		cout << "2 - ��������� ��������� " << endl;
		cout << "3 - �������� ����� ���������� ���� " << endl;
		cout << "0 - �����" << endl;;

		cout << endl
			<< ">> ";
		cin >> i;

		switch (i)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "����� ����������� ������, ��������� ���� �����" << endl;
			break;
		}
	}
}

void Chat::showChat() const // ���������� ������������ ���������, ����������� ������������ ��� ����
{
	string who;
	string to;

	cout << "������ ���������" << endl;

	for (auto& mess : messages_)
	{
		// ���������� ���������: �� �������� ������������, ��� ���� � ��� ����
		if (currentUser_->getUserLogin() == mess.getWho() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			
			who = (currentUser_->getUserLogin() == mess.getWho()) ? "�" : getUserByLogin(mess.getWho())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(����(all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "�" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "��������� ��: " << who << " ����: " << to << endl;
			cout << "�����: " << mess.getText() << endl;

		}
	}
	cout << "" << endl;
}

void Chat::addMessage() // �������� ���������
{
	string to, text;

	cout << "������� ��� ������������ - ���� ������ ��������, ��� ������� 'all' - ��� �������� ���� ����������: ";
	cin >> to;
	cout << "���������: ";
	cin.ignore();	// ������������ ����� ��������� ����������� �������
	getline(std::cin, text); // ���� ���������� ��������� � ���������

	if (!(to == "all" || getUserByName(to))) // ���� �� ������� ����� ���������� �� �����
	{
		cout << "������������ � ����� ������ �� ������ " << to << endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

void Chat::showAllUsersName() const //�������� ����� ���������������� �������������
{
	cout << "����� ���������� ���� " << endl;
	for (auto& user : users_)
	{
		cout << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
			cout << "(�)";
			cout << endl;
	}
	cout << "" << endl;
}


void Chat::login() // ����������� � ��� �� ��� ���������� ������ � ������
{
	string login;
	string password;
	char i;

	do
	{
		cout << "�����: ";
		cin >> login;
		cout << "������: ";
		cin >> password;


		currentUser_ = getUserByLogin(login);

		//if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))	//��� ������� ����
		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()) || login_func(login, password))
		{
			currentUser_ = nullptr;

			cout << "������ �����" << endl;
			cout << "������� '0' ����� ����� ��� ������ ������ ����� ��������� ����: ";
			cin >> i;

			if (i == '0')
				break;

		}
	} while (!currentUser_);
}


void Chat::signUp() // ����������� ������������ � ���� (����������������)
{
	string login, password, name;

	cout << "�����: ";
	cin >> login;
	cout << "������: ";
	cin >> password;
	cout << "��� ������������: ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	User* currentUser_ =  new User(user);
	int hash = hash_func(password);	//��� �������
	data[data_count++] = AuthData(login, &hash);//��������� � ����� � ������ � ������ ������� �� ��������������
}


User* Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : users_) // ���� �������� �� ����� ������� �������������
	{
		if (login == user.getUserLogin()) // �������� ���������� ������
		return new User (user);
	}
	return nullptr;
}

User* Chat::getUserByName(const std::string& name) 
{
	for (auto& user : users_)
	{
		if (name == user.getUserName())
		return new User (user);
	}
	return nullptr;
}

int Chat::hash_func(string pass_name) //��� ������� ������� ������������� ������������.
{
	int mem_size = 100;	//����� ����� ��� �� 100
	// ��������� ������
	int sum = 0, i = 0;
	for (; i < pass_name.length(); i++)
	{
		sum += pass_name[i];
	}
	int offset = pass_name.length();	
	// ������������ �����
	return (sum % mem_size + offset * offset) % mem_size;
}

bool Chat::login_func(string _login, string _pass)
{
	// ��� ���
	// ����� ������� true � ������ ��������� ������
	int i = 0;
	for (; i < data_count; i++)
	{
		AuthData& ad = data[i];
		//if (!strcmp(ad.login, _login)) //��� ������� ����
		if (!(ad.login == _login))
		{
			break;
		}
	}
	if (i >= data_count)
		return false;

	//int* digest = sha1(_pass, pass_length);
	int hash_int = hash_func(_pass);
	int* digest = &hash_int;
	bool cmpHashes = !memcmp(data[i].pass_hash_func, digest, SHA1HASHLENGTHBYTES);
	delete[] digest;

	return cmpHashes;
}