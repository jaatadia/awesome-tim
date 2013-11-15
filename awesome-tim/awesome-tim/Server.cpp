#include "Server.h"
#include "ClientMessage.h"

Server::Server(MaquinaEstados * juego)
{
	try
	{
		this->_socket = new ServerSocket();
		this->juego = juego;
		this->ultimoId = 0;
		this->_thread.resume();
		PrintIP();
	} catch (SocketException &sE)
	{
		cout << sE.what() << endl;
	}
}

void Server::initThread()
{

}

bool isDead(CommunicationManager* com){
	return com->getActiveState();
}

void Server::run()
{
	try
	{
		while(!this->finalizando)
		{
			Socket* sok = this->_socket->acceptConnection();
			int prox = this->juego->getNextClient();
			if (prox == -1){
				delete sok;
			}else{
				CommunicationManager* com = new CommunicationManager(sok, this->juego, true, prox);
				this->commMgrLst.push_back(com);
				this->juego->addClient(prox);
			}
			commMgrLst.remove_if(isDead);
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