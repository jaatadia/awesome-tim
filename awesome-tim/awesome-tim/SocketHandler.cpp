#include "SocketHandler.h"

SocketHandler::SocketHandler(void)
{
	this->msgRemainder = "";
}

SocketHandler::SocketHandler(Socket * socket, int mode,MessageHandler* m_handler) : _socket(socket), ConnectionManager(mode)
{
	this->m_handler = m_handler;
	this->msgRemainder = "";
}

SocketHandler::~SocketHandler(void)
{
}

void SocketHandler::initThread()
{

}

void SocketHandler::flushThread()
{

}

void SocketHandler::run()
{
	while(!this->finalizando)
	{
		switch(getMode())
		{
			case READ_MODE:
				{
					int pos = 0;
					string cadena;
					try
					{
						cadena = this->_socket->read();
					} catch (SocketException &sE)
					{
						cout << sE.what() << endl;
						this->kill();
					}
					if (cadena.size())
					{
						cadena = msgRemainder + cadena;
						pos = cadena.find_last_of("$");
						if (pos > 0 && pos < cadena.size())
						{
							this->msgRemainder = cadena.substr(pos + 1);
							cadena = cadena.substr(0, pos + 1);
						}else{
							this->msgRemainder = cadena;
							continue;
						}
						while((pos = cadena.find("$")) > 0)
						{
							Message * msg = NULL;
							int npos = cadena.find("|");
							int type = std::atoi(cadena.substr(0,npos).c_str());
							if (type)
							{
								switch(type)
								{
									case MSG_TYPE_FILES:
										msg = new FilesMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_EVENT_MOUSEBUTTONDOWN:
										msg = new MouseDownMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_GOODBYE:
										msg = new GoodbyeMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_ID:
										msg = new IdMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_CREATE_FIGURE:
										msg = new CreateFigureMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_CLIENT_MESSAGE:
										msg = new ClientMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_TRANSFORM_FIGURE:
										msg = new TransformFigureMessage(cadena.substr(npos+1));
										break;
								}

								if (msg->validate())
								{
									//this->pushInputMessage(msg);
									m_handler->pushInputMessage(msg);
								}
								else
								{
									cout << "Mensaje invalido: " << cadena << endl;
								}
								cadena = cadena.substr(pos + 1);
							}
						}
					}
					break;
				}
			case WRITE_MODE:
				Message * msg = this->getOutputMessage();
				while(msg!=NULL){
					try
					{
						this->_socket->write(msg->serialize());
					} catch (SocketException &sE)
					{
						cout << sE.what() << endl;
						this->kill();
						break;
					}
					msg = this->getOutputMessage();
				}
				this->_thread.sleep(100);
				break;
		}
	}
}