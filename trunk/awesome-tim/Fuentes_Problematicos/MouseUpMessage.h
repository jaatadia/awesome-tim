#ifndef __MOUSEUPMESSAGE_H__
#define __MOUSEUPMESSAGE_H__

#include "MouseEventMessage.h"

class MouseUpMessage : public MouseEventMessage
{
public:
	MouseUpMessage(string msg);
	virtual ~MouseUpMessage(void);
};

#endif // __MOUSEUPMESSAGE_H__