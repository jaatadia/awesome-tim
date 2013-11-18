#pragma once

#include "Message.h"

class FigureMessage: public Message
{
public:
	FigureMessage(void);
	FigureMessage(string msg);
	~FigureMessage(void);
	string serialize();
	
	void setFigureID(int figureID);
	int getFigureID();



private:
	int figureID;
};
