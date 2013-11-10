#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(Socket * socket, int type)
{
	this->socketReader = new SocketHandler(socket, READ_MODE);
	this->socketWriter = new SocketHandler(socket, WRITE_MODE);
	if(type == SERVER_TYPE)
	{
		this->messageReader = new ClientHandler(READ_MODE);
		this->messageWriter = new ClientHandler(WRITE_MODE);
	}
	else
	{
		this->messageReader = new ServerHandler(READ_MODE);
		this->messageWriter = new ServerHandler(WRITE_MODE);
	}
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