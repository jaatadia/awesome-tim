#pragma once

#include "Message.h"
#define A_CONNECT 0
#define A_DISCONECT 1
#define A_READY 2
#define A_UNREADY 3

class ClientMessage: public Message
{
public:
	ClientMessage(void);
	ClientMessage(string msg);
	virtual string serialize();
	~ClientMessage(void);
	void setAction(int action);
	void setClientID(int clientID);
	int getAction();
	int getClientID();
protected:
	int clientID;
	int action;
};
