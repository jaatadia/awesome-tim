#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(void)
{
	setState(0);
	this->_thread.resume();
}

ConnectionHandler::ConnectionHandler(Socket * s, int mode)
{
	this->_socket = s;
	setState(0);
	setMode(mode);
	this->_thread.resume();
}

ConnectionHandler::~ConnectionHandler(void)
{
}

void ConnectionHandler::initThread()
{

}

void ConnectionHandler::flushThread()
{

}

void ConnectionHandler::run()
{
	while(!this->finalizando)
	{
		switch(getMode())
		{
			case READ_MODE:
				{
					int pos = 0;
					string cadena = this->_socket->read();
					if (cadena.size())
					{
						cadena = msgRemainder + cadena;
						pos = cadena.find_last_of("$");
						if (pos > 0 && pos < cadena.size())
						{
							this->msgRemainder = cadena.substr(pos + 1);
							cadena = cadena.substr(0, pos + 1);
						}
						while((pos = cadena.find("$")) > 0)
						{
							Message * msg;
							int type = std::atoi(cadena.substr(0,1).c_str());
							if (type)
							{
								switch(type)
								{
									case MSG_TYPE_GREETING:
										msg = new GreetingMessage(cadena.substr(2, pos));
										break;
									case MSG_TYPE_FILES:
										msg = new FilesMessage(cadena.substr(2));
										break;
									case MSG_TYPE_EVENT:
										msg = new EventMessage(cadena.substr(2));
										break;
									case MSG_TYPE_GOODBYE:
										msg = new GoodbyeMessage(cadena.substr(2));
										break;
								}

								if (msg->validate())
								{
									this->inputMsgLst.push_back(msg);
									cout << cadena << endl;
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
				if (!this->outputMsgLst.empty())
				{
					std::list<Message *>::iterator itLst = this->outputMsgLst.begin();
					this->_socket->write((*itLst)->serialize());
					this->outputMsgLst.pop_front();
				}
				break;
		}
		update();
	}
}

void ConnectionHandler::setState(int state)
{
	Lock lock(this->_mutex);
	this->state = state;
}

void ConnectionHandler::setMode(int mode)
{
	Lock lock(this->_mutex);
	this->mode = mode;
}

int ConnectionHandler::getState()
{
	Lock lock(this->_mutex);
	return this->state;
}

int ConnectionHandler::getMode()
{
	Lock lock(this->_mutex);
	return this->mode;
}