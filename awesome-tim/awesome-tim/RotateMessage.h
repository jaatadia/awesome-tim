#pragma once

#include "Message.h"

class RotateMessage: public Message
{
public:
	RotateMessage(void);
	RotateMessage(string msg);
	~RotateMessage(void);
	string serialize();

	int getFigureID();
	double getAngle();

	void setFigureID(int ID);
	void setAngle(double angle);

private:
	int figureID;
	double angle;
};
