#pragma once

#include "FigureMessage.h"

class CloseScissorMessage: public FigureMessage
{
public:
	CloseScissorMessage(void);
	CloseScissorMessage(string);
	~CloseScissorMessage(void);
};
