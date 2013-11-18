#pragma once

#include "Message.h"

class VictoryMessage: public Message
{
public:
	VictoryMessage(void);
	VictoryMessage(string msg);
	~VictoryMessage(void);
	string serialize();
};
