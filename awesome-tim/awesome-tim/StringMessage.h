#pragma once

#include "Message.h"

class StringMessage: public Message
{
public:
	StringMessage(void);
	StringMessage(string msg);
	~StringMessage(void);
	
	void setString(string cadena);
	string getString();

	string serialize();

private:
	string cadena;

};
