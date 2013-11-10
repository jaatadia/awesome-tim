#include "Server.h"

Server::Server()
{
	try
	{
		this->_socket = new ServerSocket();
	} catch (SocketException &sE)
	{
		cout << sE.what() << endl;
	}
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
			this->commMgrLst.push_back(new CommunicationManager(this->_socket->acceptConnection(), SERVER_TYPE));
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