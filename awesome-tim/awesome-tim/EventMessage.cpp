#include "EventMessage.h"

EventMessage::EventMessage(string msg)
{
	//ToDo
}

EventMessage::~EventMessage()
{

}

string EventMessage::serialize()
{
	string retorno = this->type + "";
	return retorno;
}