#ifndef __GOODBYEMESSAGE_H__
#define __GOODBYEMESSAGE_H__

#include "Message.h"

class GoodbyeMessage : public Message
{
public:
	GoodbyeMessage(string msg);
	virtual ~GoodbyeMessage(void);
	virtual string serialize();
};

#endif // __GOODBYEMESSAGE_H__