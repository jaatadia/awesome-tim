#pragma once

#include "Message.h"

class InteractMessage: public Message
{
public:
	InteractMessage(void);
	InteractMessage(string msg);
	~InteractMessage(void);
	string serialize();


	void setFigureID(int id);
	int getFigureID();
	void setAction(int id);
	int getAction();

private:
	int figureID;
	int action;
};
