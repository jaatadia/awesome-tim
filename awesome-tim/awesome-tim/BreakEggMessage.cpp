#include "BreakEggMessage.h"

BreakEggMessage::BreakEggMessage(void)
{
	this->type = MSG_TYPE_BREAK_EGG;
}

BreakEggMessage::BreakEggMessage(string msg):FigureMessage(msg)
{
	this->type = MSG_TYPE_BREAK_EGG;
}

BreakEggMessage::~BreakEggMessage(void)
{
}
