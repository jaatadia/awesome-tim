#ifndef __CREATEFIGUREMESSAGE_H__
#define __CREATEFIGUREMESSAGE_H__

#include "Message.h"
#include <sstream>

/*
CreateFigureMessage cFM = new CreateFigureMessage();
cFM->setX(x);
cFM->setY(y);
this->maq->pushMesssage(cFM);
*/

class CreateFigureMessage : public Message
{
public:
	CreateFigureMessage(string msg);
	CreateFigureMessage(void);
	virtual ~CreateFigureMessage(void);
	virtual string serialize();
	int getId();
	int getFigureType();
	int getFigureID();
	double getX();
	double getY();
	double getAngle();
	bool isInAir();
	void setId(int id);
	void setFigureType(int type);
	void setFigureID(int figureID);
	void setX(double x);
	void setY(double y);
	void setAngle(double angle);
	void setInAir(bool inAir);

private:
	int id;
	int figureType;
	int figureID;
	double x;
	double y;
	double angle;
	bool inAir;
};

#endif // __CREATEFIGUREMESSAGE_H__