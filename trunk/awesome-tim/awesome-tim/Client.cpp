#include "Client.h"

Client::Client(void)
{
	this->socket = new ClientSocket("127.0.0.1");
	this->rdrServer = new ServerHandler(this->socket, READ_MODE);
	this->wrtServer = new ServerHandler(this->socket, WRITE_MODE);
}

Client::~Client(void)
{
}
