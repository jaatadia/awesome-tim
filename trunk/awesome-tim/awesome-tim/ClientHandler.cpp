#include "ClientHandler.h"

ClientHandler::ClientHandler(int mode, MaquinaEstados * game, int id) : MessageHandler(mode, game, id)
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
				if (this->getState() == 0) // EVENTOS DE SERVER
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
					msg->setId(this->id);
					this->pushOutputMessage(msg);
					std::cout<<"envie el id\n";

					ClientMessage* c_msg = new ClientMessage();
					c_msg->setClientID(this->id);
					c_msg->setAction(A_CONNECT);
					this->game->pushProcessMessage(c_msg);

					this->setState(1);
				}
				else // EVENTOS DE JUEGO
				{
					Message * msg = this->game->getSendMessage(this->id);
					if(msg)
					{
						this->pushOutputMessage(msg);
					}
				}
				break;
			case READ_MODE:
				Message * msg = this->getInputMessage();
				if(msg)
				{
					this->game->pushProcessMessage(msg);
				}
		}
		this->_thread.sleep(100);
	}
}