#include "CloseScissorMessage.h"

CloseScissorMessage::CloseScissorMessage(void)
{
	this->type = MSG_TYPE_CLOSE_SCISSOR;
}

CloseScissorMessage::CloseScissorMessage(string msg):FigureMessage(msg)
{
	this->type = MSG_TYPE_CLOSE_SCISSOR;
}

CloseScissorMessage::~CloseScissorMessage(void)
{
}
