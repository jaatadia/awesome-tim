#include "SocketHandler.h"

SocketHandler::SocketHandler(void)
{
	this->msgRemainder = "";
}

SocketHandler::SocketHandler(Socket * socket, int mode) : _socket(socket), ConnectionManager(mode)
{
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
						std::cout<<cadena<<"\n";
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
							Message * msg;
							int type = std::atoi(cadena.substr(0,1).c_str());
							if (type)
							{
								switch(type)
								{
									case MSG_TYPE_FILES:
										msg = new FilesMessage(cadena.substr(2));
										break;
									case MSG_TYPE_EVENT_MOUSEBUTTONDOWN:
										msg = new MouseDownMessage(cadena.substr(2));
										break;
									case MSG_TYPE_GOODBYE:
										msg = new GoodbyeMessage(cadena.substr(2));
										break;
									case MSG_TYPE_ID:
										msg = new IdMessage(cadena.substr(2));
										break;
									case MSG_TYPE_CREATE_FIGURE:
										msg = new CreateFigureMessage(cadena.substr(2));
										break;
									case MSG_TYPE_CLIENT_MESSAGE:
										msg = new ClientMessage(cadena.substr(2));
										break;
								}

								if (msg->validate())
								{
									this->pushInputMessage(msg);
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
				if(msg)
				{
					try
					{
						this->_socket->write(msg->serialize());
						std::cout<<msg->serialize()<<"\n";
					} catch (SocketException &sE)
					{
						cout << sE.what() << endl;
						this->kill();
					}
				}
				break;
		}
		this->_thread.sleep(100);
	}
}