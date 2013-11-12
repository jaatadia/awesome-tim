#include "MouseEventMessage.h"

MouseEventMessage::MouseEventMessage(string msg)
{
	this->valid = MSG_VALID;
	size_t pos = msg.find("|");
	if (pos != std::string::npos)
	{
		this->x = atoi(msg.substr(0, pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos)
		{
			this->y = atoi(msg.substr(0, pos).c_str());
			msg = msg.substr(pos + 1);
			pos = msg.find("$");
			if (pos != std::string::npos)
			{
				this->estado = atoi(msg.substr(0, pos).c_str());
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
	else
	{
		this->valid = MSG_INVALID;
	}
}

MouseEventMessage::~MouseEventMessage()
{

}

void MouseEventMessage::setX(int x)
{
	this->x = x;
}

void MouseEventMessage::setY(int y)
{
	this->y = y;
}

void MouseEventMessage::setEstado(int estado)
{
	this->estado = estado;
}

string MouseEventMessage::serialize()
{
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->x;
	ss << "|";
	ss << this->y;
	ss << "|";
	ss << this->estado;
	ss << "$";
	return ss.str();
}

int MouseEventMessage::getX()
{
	return this->x;
}

int MouseEventMessage::getY()
{
	return this->y;
}