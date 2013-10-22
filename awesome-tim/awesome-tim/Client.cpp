#include "Client.h"

Client::Client(void)
{
	this->socket = new ClientSocket("127.0.0.1");
	this->_thread.resume();
}

void Client::initThread()
{

}

void Client::run()
{
	while(!this->finalizando)
	{
		
	}
}

void Client::flushThread()
{

}

Client::~Client(void)
{
}
