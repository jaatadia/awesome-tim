#include "ServerHandler.h"

ServerHandler::ServerHandler(int mode, MaquinaEstados * game) : MessageHandler(mode, game)
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
					Message * msg = ((MEstadosCliente *)this->game)->getNextMessage();
					if (msg)
					{
						this->pushOutputMessage(msg);
					}
				}
			case READ_MODE:
				Message * mensaje = this->getInputMessage();
				if(mensaje)
				{
					switch(mensaje->getType())
					{
						case MSG_TYPE_ID:
							((MEstadosCliente *)this->game)->setId(((IdMessage *) mensaje)->getId());
							break;
						case MSG_TYPE_FILES:
							{
								ofstream file(((FilesMessage *) mensaje)->getNombre().append(".old").c_str(), ios::out | ios::app | ios::binary);
								if (file.is_open())
								{
									file << ((FilesMessage *) mensaje)->getStream().c_str();
									file.close();
								}
								else
								{
									cout << "No se pudo abrir el archivo";
								}
								break;
							}
						case MSG_TYPE_GOODBYE:
							break;
					}
				}
				break;
		}
		this->_thread.sleep(100);
	}
}