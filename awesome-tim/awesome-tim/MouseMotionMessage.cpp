#include "MouseMotionMessage.h"

MouseMotionMessage::MouseMotionMessage(string msg) : MouseEventMessage(str)
{
	this->type = MSG_TYPE_EVENT_MOUSEMOTION;
}

MouseMotionMessage::~MouseMotionMessage(void)
{
}
