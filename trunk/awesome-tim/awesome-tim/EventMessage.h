#ifndef __EVENTMESSAGE_H__
#define __EVENTMESSAGE_H__

#include "Message.h"

class EventMessage : public Message
{
public:
	EventMessage(string msg);
	virtual ~EventMessage(void);
	virtual string serialize();
};

#endif // __EVENTMESSAGE_H__