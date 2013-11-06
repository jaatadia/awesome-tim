#include "GoodbyeMessage.h"

GoodbyeMessage::GoodbyeMessage(string msg)
{
	this->type = MSG_TYPE_GOODBYE;
	//TODO Convertir msg
}

GoodbyeMessage::~GoodbyeMessage()
{

}

string GoodbyeMessage::serialize()
{
	string retorno = this->type + "";
	return retorno;
}