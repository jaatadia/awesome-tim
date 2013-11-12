#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "Constantes.h"
#include <iostream>

using namespace std;

class Message
{
public:
	virtual ~Message(void);
	virtual string serialize() = 0;
	int validate();
	int getType();

protected:
	int type;
	int valid;
};

#endif // __MESSAGE_H__