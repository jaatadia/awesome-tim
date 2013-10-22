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
			this->clientLst.push_back(new ClientHandler(socketCliente));
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

}
