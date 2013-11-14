#include "ClientMessage.h"

ClientMessage::ClientMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_CLIENT_MESSAGE;
	this->clientID = -1;
	this->action = -1;
}

ClientMessage::ClientMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_CLIENT_MESSAGE;
	size_t pos = msg.find("|");
	if (pos != std::string::npos)
	{
		this->clientID = atoi(msg.substr(0, pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("$");
		if (pos != std::string::npos)
		{
			this->action = atoi(msg.substr(0, pos).c_str());
		}
		else
		{
			this->valid = MSG_INVALID;
		}
	}
	else
	{
		this->valid = MSG_INVALID;
	}
}

void ClientMessage::setAction(int action)
{
	this->action = action;
}

void ClientMessage::setClientID(int clientID)
{
	this->clientID = clientID;
}

int ClientMessage::getAction()
{
	return this->action;
}

int ClientMessage::getClientID()
{
	return this->clientID;
}

ClientMessage::~ClientMessage(void)
{
}


string ClientMessage::serialize()
{
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->clientID;
	ss << "|";
	ss << this->action;
	ss << "$";
	return ss.str();
}