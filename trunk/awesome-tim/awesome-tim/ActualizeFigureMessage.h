#pragma once

#include "FigureMessage.h"

class ActualizeFigureMessage: public FigureMessage
{
public:
	ActualizeFigureMessage(void);
	ActualizeFigureMessage(string msg);
	~ActualizeFigureMessage(void);
};
