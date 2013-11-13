#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(Socket * socket, MaquinaEstados * game, bool server, int id)
{
	this->server = server;
	this->ID = id;
	this->socketReader = new SocketHandler(socket, READ_MODE);
	this->socketWriter = new SocketHandler(socket, WRITE_MODE);
	if(server){
		this->messageReader = new ClientHandler(READ_MODE, game, id);
		this->messageWriter = new ClientHandler(WRITE_MODE, game, id);
	}else{
		this->messageReader = new ServerHandler(READ_MODE, game, id);
		this->messageWriter = new ServerHandler(WRITE_MODE, game, id);
	}
	this->game = game;
	this->_thread.resume();
}

CommunicationManager::~CommunicationManager(void)
{
}


void CommunicationManager::initThread()
{

}

void CommunicationManager::flushThread()
{

}

void CommunicationManager::run()
{
	while(!this->finalizando)
	{
		Message * msg = this->messageWriter->getOutputMessage();
		if(msg)
		{
			this->socketWriter->pushOutputMessage(msg);
		}
		msg = this->socketReader->getInputMessage();
		if(msg)
		{
			try{
				this->messageReader->pushInputMessage(msg);
			}catch(...){
				this->finalizando = true;
				if(this->server){
					this->game->clientesConectados.remove(this->ID);
				}else{
					std::cout<<"Se perdio la conexion con el servivdor\n";
					this->game->salir();
				}
			}
		}
		this->_thread.sleep(100);
	}
}