#pragma once

#include "FigureMessage.h"

class RemoveFigureMessage: public FigureMessage
{
public:
	RemoveFigureMessage(void);
	RemoveFigureMessage(string msg);
	~RemoveFigureMessage(void);
};
