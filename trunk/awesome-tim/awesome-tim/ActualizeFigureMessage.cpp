#include "ActualizeFigureMessage.h"

ActualizeFigureMessage::ActualizeFigureMessage(void)
{
	this->type = MSG_TYPE_ACTUALIZE;
}

ActualizeFigureMessage::ActualizeFigureMessage(string msg):FigureMessage(msg)
{
	this->type = MSG_TYPE_ACTUALIZE;
}


ActualizeFigureMessage::~ActualizeFigureMessage(void)
{
}
