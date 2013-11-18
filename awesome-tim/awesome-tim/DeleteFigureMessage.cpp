#include "DeleteFigureMessage.h"

DeleteFigureMessage::DeleteFigureMessage(void)
{
	this->type = MSG_TYPE_DELETE;
}

DeleteFigureMessage::DeleteFigureMessage(string msg):DropFigureMessage(msg)
{
	this->type = MSG_TYPE_DELETE;
}


DeleteFigureMessage::~DeleteFigureMessage(void)
{
}
