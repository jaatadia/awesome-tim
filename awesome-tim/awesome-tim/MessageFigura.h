#pragma once
#include "EventMessage.h"

class MessageFigura :	public EventMessage
{
public:
	MessageFigura(string msg);
	~MessageFigura(void);
	virtual string serialize();

	int getSubtipoMsj();
	int getIdFigura();
	string getData1();
	string getData2();
	string getData3();

private:
	//los campos que espero que tenga
	int subtipoMsj;
	int idFigura;
	string data1;
	string data2;
	string data3;
};
