#ifndef __MOUSEMOTIONMESSAGE_H__
#define __MOUSEMOTIONMESSAGE_H__

#include "MouseEventMessage.h"

class MouseMotionMessage : public MouseEventMessage
{
public:
	MouseMotionMessage(string msg);
	MouseMotionMessage(void);
	virtual ~MouseMotionMessage(void);

private:
	int estado;
};

#endif // __MOUSEMOTIONMESSAGE_H__