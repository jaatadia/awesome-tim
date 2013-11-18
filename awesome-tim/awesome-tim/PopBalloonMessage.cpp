#include "PopBalloonMessage.h"

PopBalloonMessage::PopBalloonMessage(void)
{
	this->type = MSG_TYPE_POP_BALLOON;
}

PopBalloonMessage::PopBalloonMessage(string msg):FigureMessage(msg)
{
	this->type = MSG_TYPE_POP_BALLOON;
}

PopBalloonMessage::~PopBalloonMessage(void)
{
}
