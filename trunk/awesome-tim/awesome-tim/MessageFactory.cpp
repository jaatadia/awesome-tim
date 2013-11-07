#include "MessageFactory.h"

#include <stdlib.h>

Message * MessageFactory::deserialize(string msg)
{
	if (msg.size())
	{
		int type = msg.c_str()[0];//std::stoi(msg.substr(0,1));no existe esta funcion en nuestro entonrno!!!!
		if (type)
		{
			switch(type)
			{
				case MSG_TYPE_GREETING:
					return new GreetingMessage(msg.substr(2));
					break;
				case MSG_TYPE_FILES:
					return new FilesMessage(msg.substr(2));
					break;
				case MSG_TYPE_EVENT:
					return new EventMessage(msg.substr(2));
					break;
				case MSG_TYPE_GOODBYE:
					return new GoodbyeMessage(msg.substr(2));
					break;
			}
		}
	}
}