#pragma once
#include <string>;
using namespace std;

class Message
{
public:
	Message(const string _who, const string _to, const string _text);
		
	const string& getWho() const;
	const string& getTo() const;
	const string& getText() const;

private:
	string who;		// ��� �������� ���������
	string to;		// ���� ��������� ���������
	string text;	// ����� 
};