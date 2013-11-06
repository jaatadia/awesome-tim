#include "Server.h"

Server::Server()
{
	this->socket = new ServerSocket();
}

void Server::initThread()
{

}

void Server::run()
{
	try
	{
		while(!this->finalizando)
		{
			Socket * socketCliente = this->socket->acceptConnection();
			this->clientRdrLst.push_back(new ClientHandler(socketCliente, READ_MODE));
			this->clientWrtLst.push_back(new ClientHandler(socketCliente, WRITE_MODE));
		}
	} catch (SocketException &ex)
	{
		cout << ex.what() << endl;
	}
}

void Server::flushThread()
{

}

Server::~Server(void)
{
	this->_thread.waitForDeath();
}

void Server::init()
{
	this->_thread.resume();
}