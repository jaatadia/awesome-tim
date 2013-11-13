#include "ServerHandler.h"

ServerHandler::ServerHandler(int mode, MaquinaEstados * game, int id) : MessageHandler(mode, game, id)
{
}

ServerHandler::~ServerHandler(void)
{
}

void ServerHandler::initThread()
{
}

void ServerHandler::flushThread()
{
}

void ServerHandler::run()
{
	while(!this->finalizando)
	{
		switch(getMode())
		{
			case WRITE_MODE:
				{
					Message * msg = ((MEstadosCliente *)this->game)->getSendMessage(this->id);
					if (msg)
					{
						this->pushOutputMessage(msg);
					}
				}
			case READ_MODE:
				Message * mensaje = this->getInputMessage();
				if(mensaje)
				{
					if(mensaje->getType() == MSG_TYPE_ID)
					{
						this->id = ((IdMessage *) mensaje)->getId();
						this->game->setId(this->id);
						((MEstadosCliente *)this->game)->init(((IdMessage *) mensaje)->getId());
					}
					else if (mensaje->getType() == MSG_TYPE_FILES)
					{
						ofstream file(((FilesMessage *) mensaje)->getNombre().c_str(), ios::out | ios::app | ios::binary);
						if (file.is_open())
						{
							file << ((FilesMessage *) mensaje)->getStream().c_str();
							file.close();
						}
						else
						{
							cout << "No se pudo abrir el archivo";
						}
					}
					else
					{
						this->game->pushProcessMessage(mensaje);
					}
				}
		}
		this->_thread.sleep(100);
	}
}