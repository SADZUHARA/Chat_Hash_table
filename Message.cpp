#pragma once
#include <string>;
#include "Message.h"
using namespace std;

Message::Message(const string _who, const string _to, const string _text)
{
	who = _who;
	to = _to;
	text = _text;
}

const string& Message::getWho() const
{
	return this->who;
}

const string& Message::getTo() const
{
	return to;
}

const string& Message::getText() const
{
	return text;
}