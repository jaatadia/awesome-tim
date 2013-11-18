#pragma once

#include "Message.h"

class DropFigureMessage: public Message
{
public:
	DropFigureMessage(void);
	DropFigureMessage(string msg);
	~DropFigureMessage(void);

	string serialize();
	void setClientID(int id);
	int getClientID();
	void setFigureID(int id);
	int getFigureID();

private:
	int clientID;
	int figureID;
	
};
