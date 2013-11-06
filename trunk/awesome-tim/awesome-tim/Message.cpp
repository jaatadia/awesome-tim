#include "Message.h"

Message::~Message()
{

}

string Message::serialize()
{
	return (this->type + "");
}

int Message::validate()
{
	return this->valid;
}

int Message::getType()
{
	return this->type;
}