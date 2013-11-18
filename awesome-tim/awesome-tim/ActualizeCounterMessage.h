#pragma once

#include "VictoryMessage.h"

class ActualizeCounterMessage: public VictoryMessage
{
public:
	ActualizeCounterMessage(void);
	ActualizeCounterMessage(string msg);
	~ActualizeCounterMessage(void);
};
