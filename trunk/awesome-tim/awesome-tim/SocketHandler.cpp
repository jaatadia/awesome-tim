#include "SocketHandler.h"
#include "MEstadosCliente.h"

SocketHandler::SocketHandler(void)
{
	this->msgRemainder = "";
}

SocketHandler::SocketHandler(Socket * socket, int mode,MessageHandler* m_handler,MaquinaEstados* maq,int id) : _socket(socket), ConnectionManager(mode)
{
	this->m_handler = m_handler;
	this->msgRemainder = "";
	this->maq = maq;
	this->id = id;
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
	if(getMode()==WRITE_MODE){
		while(this->id<0&&!this->finalizando){
			this->id = this->maq->getId();
			this->_thread.sleep(1000);
		}
	}
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
										this->id = ((IdMessage*)msg)->getId();
										maq->setId(this->id);
										((MEstadosCliente*)maq)->init(id);
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
									case MSG_TYPE_CREATE_BUTTON:
										msg = new CreateButtonMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_SET_AREA:
										msg = new SetAreaMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_UNION1:
										msg = new UnionMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_UNION2:
										msg = new UnionMessage2(cadena.substr(npos+1));
										break;
									case MSG_TYPE_ACTUALIZE:
										msg = new ActualizeFigureMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_REMOVE:
										msg = new RemoveFigureMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_CLOSE_SCISSOR:
										msg = new CloseScissorMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_POP_BALLOON:
										msg = new PopBalloonMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_FIRE_BOW:
										msg = new FireBowMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_FIRE_SHOTGUN:
										msg = new FireShotgunMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_VICTORY:
										msg = new VictoryMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_ROTATE:
										msg = new RotateMessage(cadena.substr(npos+1));
										break;
									case MSG_TYPE_BREAK_EGG:
										msg = new BreakEggMessage(cadena.substr(npos+1));
										break;
								}

								if (msg!=NULL && msg->validate())
								{
									//this->pushInputMessage(msg);
									//m_handler->pushInputMessage(msg);
									this->maq->pushProcessMessage(msg);;
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
				//Message * msg = this->getOutputMessage();
				Message * msg = this->maq->getSendMessage(this->id);
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
					//msg = this->getOutputMessage();
					msg = this->maq->getSendMessage(this->id);
				}
				this->_thread.sleep(100);
				break;
		}
	}
}