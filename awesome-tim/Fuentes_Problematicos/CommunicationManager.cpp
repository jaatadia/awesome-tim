#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(Socket * socket, MaquinaEstados * game)
{
	this->socketReader = new SocketHandler(socket, READ_MODE);
	this->socketWriter = new SocketHandler(socket, WRITE_MODE);
#ifdef SERVER_MODE
	this->messageReader = new ClientHandler(READ_MODE, game);
	this->messageWriter = new ClientHandler(WRITE_MODE, game);
#else
	this->messageReader = new ServerHandler(READ_MODE, game);
	this->messageWriter = new ServerHandler(WRITE_MODE, game);
#endif // SERVER_MODE
	this->juego = juego;
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
			this->messageReader->pushInputMessage(msg);
		}
		this->_thread.sleep(100);
	}
}