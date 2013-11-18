#include "RemoveFigureMessage.h"

RemoveFigureMessage::RemoveFigureMessage(void)
{
	this->type = MSG_TYPE_REMOVE;
}

RemoveFigureMessage::RemoveFigureMessage(string msg):FigureMessage(msg)
{
	this->type = MSG_TYPE_REMOVE;
}

RemoveFigureMessage::~RemoveFigureMessage(void)
{
}
