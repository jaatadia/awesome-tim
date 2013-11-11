#ifndef __MOUSEMOTIONMESSAGE_H__
#define __MOUSEMOTIONMESSAGE_H__

#include "MouseEventMessage.h"

class MouseMotionMessage : public MouseEventMessage
{
public:
	MouseMotionMessage(string msg);
	virtual ~MouseMotionMessage(void);
};

#endif // __MOUSEMOTIONMESSAGE_H__