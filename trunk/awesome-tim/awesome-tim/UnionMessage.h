#pragma once

#include "Message.h"

class UnionMessage: public Message
{
public:
	UnionMessage(void);
	UnionMessage(string msg);
	~UnionMessage(void);
	string serialize();

	void setClientID(int id);
	int getClientID();

	void setFigsNum(int numFig,double x,double y);
	void getFigsNum(int* numFig,double* x,double* y);

private:
	int clientID;
	int numFig;
	double x;
	double y;
};
