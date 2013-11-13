#include "ClientHandler.h"

ClientHandler::ClientHandler(int mode, MaquinaEstados * game) : MessageHandler(mode, game)
{
}

ClientHandler::~ClientHandler(void)
{
}

void ClientHandler::initThread()
{
}

void ClientHandler::flushThread()
{
}

void ClientHandler::run()
{
	while(!this->finalizando)
	{
		switch(this->getMode())
		{
			case WRITE_MODE:
				if (this->getState() == 0)
				{
					// Envio Yaml
					string nombreArchivo = "archivoDefault.yaml";
					char buffer[TAM_BUFFER];
					ifstream archivoPrueba(nombreArchivo.c_str(), ios::in | ios::binary);
					if(!archivoPrueba.fail())
					{
						while (!archivoPrueba.eof() && archivoPrueba.good())
						{
							archivoPrueba.read(buffer, TAM_BUFFER - 5 - nombreArchivo.size());
							int numBytes = archivoPrueba.gcount();
							string aux;
							for(int i = 0; i < numBytes; i++)
							{
								aux += buffer[i];
							}
							string msg = "";
							msg.append(nombreArchivo).append("|").append(aux).append("$");

							Message * fM = new FilesMessage(msg);
							if (fM->validate())
							{
								this->pushOutputMessage(fM);
							}
						}
						archivoPrueba.close();
					}

					// Envio ID
					IdMessage * msg = new IdMessage();
					msg->setId(this->game->getId());
					this->pushOutputMessage(msg);

					this->setState(1);
				}
				break;
			case READ_MODE:
				Message * msg = this->getInputMessage();
				if(msg)
				{
					switch(msg->getType())
					{
						case MSG_TYPE_ID:
							break;
						case MSG_TYPE_FILES:
							break;
						case MSG_TYPE_EVENT_MOUSEBUTTONDOWN:
							break;
						case MSG_TYPE_GOODBYE:
							break;
					}
				}
		}
		this->_thread.sleep(100);
	}
}