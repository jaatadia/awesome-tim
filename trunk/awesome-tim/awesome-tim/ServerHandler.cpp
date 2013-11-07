#include "ServerHandler.h"

ServerHandler::ServerHandler(void)
{
}

ServerHandler::ServerHandler(Socket * s, int mode) : ConnectionHandler(s, mode)
{
}

ServerHandler::~ServerHandler(void)
{
}

void ServerHandler::update()
{
	switch(getMode())
	{
		case WRITE_MODE:
			break;
		case READ_MODE:
			Message * mensaje = (Message *)this->inputMsgLst.front();
			this->inputMsgLst.pop_front();
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
				case MSG_TYPE_EVENT:
					break;
				case MSG_TYPE_GOODBYE:
					break;
			}
			break;
	}
}