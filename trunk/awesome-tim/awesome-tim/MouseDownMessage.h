#ifndef __MOUSEDOWNMESSAGE_H__
#define __MOUSEDOWNMESSAGE_H__

#include "MouseEventMessage.h"

class MouseDownMessage : public MouseEventMessage
{
public:
	MouseDownMessage(string msg);
	virtual ~MouseDownMessage(void);
};

#endif // __MOUSEDOWNMESSAGE_H__