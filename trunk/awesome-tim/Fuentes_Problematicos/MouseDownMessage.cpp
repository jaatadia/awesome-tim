#include "MouseDownMessage.h"

MouseDownMessage::MouseDownMessage(string msg) : MouseEventMessage(msg)
{
	this->type = MSG_TYPE_EVENT_MOUSEBUTTONDOWN;
}

MouseDownMessage::~MouseDownMessage(void)
{
}
