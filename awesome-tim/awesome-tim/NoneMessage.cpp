#include "NoneMessage.h"

NoneMessage::NoneMessage(void)
{
	this->type = MSG_TYPE_NONE;
	this->valid = MSG_VALID;
}

NoneMessage::NoneMessage(string msg):VictoryMessage(msg)
{
	this->type = MSG_TYPE_NONE;
	this->valid = MSG_VALID;
}


NoneMessage::~NoneMessage(void)
{
}
