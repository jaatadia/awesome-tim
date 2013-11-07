#ifndef __MESSAGEFACTORY_H__
#define __MESSAGEFACTORY_H__

#include "Message.h"
#include "GreetingMessage.h"
#include "FilesMessage.h"
#include "EventMessage.h"
#include "GoodbyeMessage.h"
#include "Constantes.h"
#include <iostream>

using namespace std;

class MessageFactory
{
public:
	static Message * deserialize(string msg);
	static string serialize(Message * msg);
	~MessageFactory(void);

private:
	MessageFactory(void);
};

#endif // __MESSAGEFACTORY_H__