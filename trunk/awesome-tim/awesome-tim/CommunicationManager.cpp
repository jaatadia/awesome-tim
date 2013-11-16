#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(Socket * socket, MaquinaEstados * game, bool server, int id)
{
	this->server = server;
	this->ID = id;

	this->socketWriter = new SocketHandler(socket, WRITE_MODE,NULL,game,id);
	this->socketReader = new SocketHandler(socket, READ_MODE,NULL,game,id);
	if(server){
		//this->socketWriter = new SocketHandler(socket, WRITE_MODE,NULL,game);
		//this->messageWriter = new ClientHandler(WRITE_MODE, game, id,this->socketWriter);
		//this->messageReader = new ClientHandler(READ_MODE, game, id,NULL,game);
		//this->socketReader = new SocketHandler(socket, READ_MODE,this->messageReader);
		
		
	}else{
		//this->socketWriter = new SocketHandler(socket, WRITE_MODE,NULL);
		//this->messageWriter = new ServerHandler(WRITE_MODE, game, id,this->socketWriter);
		//this->messageReader = new ServerHandler(READ_MODE, game, id,NULL);
		//this->socketReader = new SocketHandler(socket, READ_MODE,this->messageReader);
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
		//Message * msg = this->messageWriter->getOutputMessage();
		//if(msg)
		//{
		//	this->socketWriter->pushOutputMessage(msg);
		//}
		//msg = this->socketReader->getInputMessage();
		//if(msg)
		//{
		//	this->messageReader->pushInputMessage(msg);
		//}
		this->_thread.sleep(5000);

		
		if((socketWriter->getActiveState())||(socketReader->getActiveState())){
			if(!socketWriter->getActiveState()) socketWriter->kill();
			if(!socketReader->getActiveState()) socketReader->kill();
			//messageWriter->kill();
			//messageReader->kill();
			delete socketWriter;
			delete socketReader;
			//delete messageWriter;
			//delete messageReader;
			this->kill();
			if(server){
				ClientMessage* c_msg = new ClientMessage();
				c_msg->setClientID(this->ID);
				c_msg->setAction(A_DISCONECT);
				this->game->pushProcessMessage(c_msg);
			}else{
				std::cout<<"Se perdio la Conexion con el servidor. Cerrando el programa...\n";
				this->game->salir();
			}
		}

	}
}