#pragma once

#include "FigureMessage.h"

class PopBalloonMessage: public FigureMessage
{
public:
	PopBalloonMessage(void);
	PopBalloonMessage(string msg);
	~PopBalloonMessage(void);
};
