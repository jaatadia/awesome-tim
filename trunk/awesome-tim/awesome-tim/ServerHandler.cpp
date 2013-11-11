#include "ServerHandler.h"

ServerHandler::ServerHandler(int mode) : MessageHandler(mode)
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
				break;
			case READ_MODE:
				Message * mensaje = this->getInputMessage();
				if(mensaje)
				{
					switch(mensaje->getType())
					{
						case MSG_TYPE_GREETING:
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
						case MSG_TYPE_EVENT_MOUSEBUTTONDOWN:
							break;
						case MSG_TYPE_GOODBYE:
							break;
					}
				}
				break;
		}
		this->_thread.sleep(100);
	}
}