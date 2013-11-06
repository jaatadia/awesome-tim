#ifndef __GREETINGMESSAGE_H__
#define __GREETINGMESSAGE_H__

#include "Message.h"

class GreetingMessage : public Message
{
public:
	GreetingMessage(string msg);
	virtual ~GreetingMessage(void);
	virtual string serialize();
};

#endif // __GREETINGMESSAGE_H__