#include "GreetingMessage.h"

GreetingMessage::GreetingMessage(string msg)
{
	this->type = MSG_TYPE_GREETING;
	//TODO Convertir msg
}

GreetingMessage::~GreetingMessage()
{

}

string GreetingMessage::serialize()
{
	string retorno = this->type + "";
	return retorno;
}