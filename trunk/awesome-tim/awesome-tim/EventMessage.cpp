#include "EventMessage.h"

EventMessage::EventMessage(string msg)
{
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