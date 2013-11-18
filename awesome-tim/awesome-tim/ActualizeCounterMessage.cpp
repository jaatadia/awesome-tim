#include "ActualizeCounterMessage.h"

ActualizeCounterMessage::ActualizeCounterMessage(void)
{
	this->type = MSG_TYPE_COUNTER;
}

ActualizeCounterMessage::ActualizeCounterMessage(string msg):VictoryMessage(msg)
{
	this->type = MSG_TYPE_COUNTER;
}

ActualizeCounterMessage::~ActualizeCounterMessage(void)
{
}
