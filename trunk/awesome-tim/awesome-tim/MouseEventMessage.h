#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

#include "Message.h"

#include <sstream>

class MouseEventMessage : public Message
{
public:
	MouseEventMessage(string msg);
	virtual ~MouseEventMessage(void);
	virtual string serialize();
	int getX();
	int getY();

private:
	int x;
	int y;
};

#endif // __MOUSEEVENT_H__
