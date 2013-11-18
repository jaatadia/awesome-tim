#pragma once

#include "FigureMessage.h"

class BreakEggMessage: public FigureMessage
{
public:
	BreakEggMessage(void);
	BreakEggMessage(string msg);
	~BreakEggMessage(void);
};
