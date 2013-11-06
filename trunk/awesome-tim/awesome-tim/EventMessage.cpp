#include "EventMessage.h"

EventMessage::EventMessage(string msg)
{
	this->type = MSG_TYPE_EVENT;
	//TODO Convertir msg
}

EventMessage::~EventMessage()
{

}

string EventMessage::serialize()
{
	string retorno = this->type + "";
	return retorno;
}