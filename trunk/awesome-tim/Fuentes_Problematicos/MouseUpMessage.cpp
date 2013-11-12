#include "MouseUpMessage.h"

MouseUpMessage::MouseUpMessage(string msg) : MouseEventMessage(msg)
{
	this->type = MSG_TYPE_EVENT_MOUSEBUTTONUP;
}

MouseUpMessage::~MouseUpMessage(void)
{
}
