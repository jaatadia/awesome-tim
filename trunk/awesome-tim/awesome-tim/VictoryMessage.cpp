#include "VictoryMessage.h"

VictoryMessage::VictoryMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_VICTORY;
}

VictoryMessage::VictoryMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_VICTORY;
}


VictoryMessage::~VictoryMessage(void)
{
}

string VictoryMessage::serialize(){

	stringstream ss;
	ss << this->type;
	ss << "$";
	return ss.str();
}