#pragma once

#include "Message.h"

class SetAreaMessage: public Message
{
public:
	SetAreaMessage(void);
	SetAreaMessage(string msg);
	~SetAreaMessage(void);

	void setPuntos(double x1,double y1,double x2,double y2);
	void getPuntos(double* x1,double* y1,double* x2,double* y2);

	virtual string serialize();

private:
	double x1;
	double y1;
	double x2;
	double y2;
};
