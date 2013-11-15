#pragma once

#include "Message.h"

#define T_NONE 0
#define T_GROW 1
#define T_SHRINK 2
#define T_SHIFT 3
#define T_ROTATE 4
#define T_DROP 5 //soltar en terreno
#define T_DROPDEAD 6 //soltar y muere
#define T_REMOVE 7 //eliminar del terreno
#define T_RESTORE 8


class TransformFigureMessage: public Message
{
public:
	TransformFigureMessage(void);
	TransformFigureMessage(string msg);
	~TransformFigureMessage(void);
	virtual string serialize();

	int getClientID();
	int getFigureID();
	double getX();
	double getY();
	double getAngle();
	int getSizeChange();
	int getLength();

	void setClientID(int id);
	void setFigureID(int id);
	void setX(double x);
	void setY(double y);
	void setAngle(double angle);
	void setSizeChange(int type);
	void setLength(int length);

protected:
	int clientID;
	int figureID;
	double x;
	double y;
	double angle;
	int sizeChange;
	int length;
};
