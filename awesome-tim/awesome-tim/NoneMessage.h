#pragma once

#include "VictoryMessage.h"

class NoneMessage: public VictoryMessage
{
public:
	NoneMessage(void);
	NoneMessage(string msg);
	~NoneMessage(void);
};
