#include "IdMessage.h"

IdMessage::IdMessage(string msg)
{
	IdMessage();
	size_t pos = msg.find("$");
	if (pos != std::string::npos)
	{
		this->id = atoi(msg.substr(0, pos).c_str());
	}
	else
	{
		this->valid = MSG_INVALID;
	}
}

IdMessage::IdMessage()
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_ID;
}

IdMessage::~IdMessage()
{

}

int IdMessage::getId()
{
	return this->id;
}

void IdMessage::setId(int id)
{
	this->id = id;
}

string IdMessage::serialize()
{
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->id;
	ss << "$";
	return ss.str();
}