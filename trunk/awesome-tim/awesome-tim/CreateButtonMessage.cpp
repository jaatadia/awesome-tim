#include "CreateButtonMessage.h"

CreateButtonMessage::CreateButtonMessage(void)
{
	this->type = MSG_TYPE_CREATE_BUTTON;
	this->valid = MSG_VALID;
}

CreateButtonMessage::CreateButtonMessage(string msg):CreateFigureMessage(msg)
{
	this->type = MSG_TYPE_CREATE_BUTTON;
}


CreateButtonMessage::~CreateButtonMessage(void)
{
}
