#include "MessageFactory.h"

static Message * MessageFactory::deserealize(string msg)
{
	if (msg.size)
	{
		int type = std::stoi(msg.substr(0,1));
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