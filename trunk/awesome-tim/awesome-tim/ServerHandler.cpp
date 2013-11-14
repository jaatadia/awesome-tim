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
					if(this->id != -1)
					{
						Message * msg = this->game->getSendMessage(this->id);
						if (msg)
						{
							this->pushOutputMessage(msg);
						}
					}
					else if (this->game->getId() >= 0)
					{
						this->id = this->game->getId();
						((MEstadosCliente *)this->game)->init(this->id);
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