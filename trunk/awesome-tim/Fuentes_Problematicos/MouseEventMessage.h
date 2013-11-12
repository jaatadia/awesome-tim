#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

#include "Message.h"

#include <sstream>

class MouseEventMessage : public Message
{
public:
	MouseEventMessage();
	MouseEventMessage(string msg);
	virtual ~MouseEventMessage(void);
	virtual string serialize();
	int getX();
	int getY();
	int getEstado();
	void setX(int x);
	void setY(int y);
	void setEstado(int estado);

private:
	int x;
	int y;
	int estado;
};

#endif // __MOUSEEVENT_H__
