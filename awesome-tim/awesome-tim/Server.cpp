#include "Server.h"

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

void Server::run()
{
	try
	{
		while(!this->finalizando)
		{
			Socket* sok = this->_socket->acceptConnection();
			int prox = -1;
			for (int i = 1;i<=juego->clientesDelJuego;i++){
				bool encontrado = false;
				for (std::list<int>::iterator iter = juego->clientesConectados.begin();iter != juego->clientesConectados.end();iter++){
					if ((*iter) == i){
						encontrado = true;
					}
				}
				if(!encontrado){
					prox = i;
					break;
				}
			}
			
			
			if (prox == -1){
				delete sok;
			}else{
				CommunicationManager* com = new CommunicationManager(sok, this->juego, true, prox);
				this->commMgrLst.push_back(com);
				juego->clientesConectados.push_back(prox);
			}
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