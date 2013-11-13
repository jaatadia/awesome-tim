#pragma once

#include "Message.h"

class MessageState : public Message
{
public:
	MessageState(string msg);
	~MessageState(void);
	virtual string serialize();

	int getEstado();

private:
	int estado;
};
