#include "Server.h"

Server::Server(MaquinaEstados * juego)
{
	try
	{
		this->_socket = new ServerSocket();
		this->juego = juego;
		this->_thread.resume();
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
			this->commMgrLst.push_back(new CommunicationManager(this->_socket->acceptConnection(), this->juego));
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