#include "ClientHandler.h"

ClientHandler::ClientHandler(void)
{
}

ClientHandler::ClientHandler(Socket * s, int mode) : ConnectionHandler(s, mode)
{
}

ClientHandler::~ClientHandler(void)
{
}

void ClientHandler::update()
{
	switch(this->mode)
	{
		case WRITE_MODE:
			if (getState() == 0)
			{
				string nombreArchivo = "C:\\15.jpg";
				char buffer[TAM_BUFFER];
				ifstream archivoPrueba(nombreArchivo.c_str(), ios::in | ios::binary);
				if(!archivoPrueba.fail())
				{
					while (!archivoPrueba.eof() && archivoPrueba.good())
					{
						archivoPrueba.read(buffer, TAM_BUFFER - 5 - nombreArchivo.size());
						int numBytes = archivoPrueba.gcount();
						string aux = buffer;
						aux = aux.substr(0,numBytes);
						string msg = "";
						msg.append(nombreArchivo).append("|").append(aux).append("$");

						Message * fM = new FilesMessage(msg);
						if (fM->validate())
						{
							this->outputMsgLst.push_back(fM);
						}
					}
					archivoPrueba.close();
				}
				setState(1);
			}
			break;
		case READ_MODE:
			if (!this->inputMsgLst.empty())
			{
				std::list<Message *>::iterator itLst = this->inputMsgLst.begin();
				switch((*itLst)->getType())
				{
					case MSG_TYPE_GREETING:
						break;
					case MSG_TYPE_FILES:
						break;
					case MSG_TYPE_EVENT:
						break;
					case MSG_TYPE_GOODBYE:
						break;
				}
			}
			break;
	}
}