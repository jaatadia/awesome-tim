#include "NoneMessage.h"

NoneMessage::NoneMessage(void)
{
	this->type = MSG_TYPE_NONE;
}

NoneMessage::NoneMessage(string msg):VictoryMessage(msg)
{
	this->type = MSG_TYPE_NONE;
}


NoneMessage::~NoneMessage(void)
{
}
