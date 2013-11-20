#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(Socket * socket, MaquinaEstados * game, bool server, int id)
{
	this->server = server;
	this->ID = id;

	this->socketWriter = new SocketHandler(socket, WRITE_MODE,NULL,game,id);
	this->socketReader = new SocketHandler(socket, READ_MODE,NULL,game,id);
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
	if((socketWriter!=NULL)&&(!socketWriter->getActiveState())) socketWriter->kill();
	if((socketReader!=NULL)&&(!socketReader->getActiveState())) socketReader->kill();
	delete socketWriter;
	delete socketReader;

}

void CommunicationManager::run()
{
	int vuelta = 0;
	while(!this->finalizando)
	{
		this->_thread.sleep(5000);

		if(this->ID<0){
			this->ID = this->game->getId();
		}
		if(this->ID>=0){
			NoneMessage* n_msg = new NoneMessage();
			this->game->returnSendMessage(n_msg,this->ID);
		}

		//vuelta++;
		//vuelta%=3;
		//if(vuelta==0){
		//	if(socketReader->mensajesRecibidos == 0){
		//		socketWriter->kill();
		//		socketReader->kill();
		//	}else{
		//		socketReader->mensajesRecibidos = 0;
		//	}
		//}

		if((socketWriter->getActiveState())||(socketReader->getActiveState())){
			if(!socketWriter->getActiveState()) socketWriter->kill();
			if(!socketReader->getActiveState()) socketReader->kill();
			delete socketWriter;
			delete socketReader;
			socketWriter = NULL;
			socketReader = NULL;
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