#ifndef __SOCKETHANDLER_H__
#define __SOCKETHANDLER_H__

#include "ConnectionManager.h"
#include "Message.h"
#include "IdMessage.h"
#include "FilesMessage.h"
#include "MouseDownMessage.h"
#include "GoodbyeMessage.h"
#include "CreateFigureMessage.h"
#include "TransformFigureMessage.h"
#include "SetAreaMessage.h"
#include "CreateButtonMessage.h"
#include "ClientMessage.h"
#include "Constantes.h"
#include "Socket.h"
#include "SocketException.h"
#include <stdlib.h>
#include "MessageHandler.h"
#include "MaquinaEstados.h"
#include "UnionMessage.h"
#include "UnionMessage2.h"
#include "RemoveFigureMessage.h"
#include "ActualizeFigureMessage.h"
#include "CloseScissorMessage.h"

class SocketHandler : public ConnectionManager
{
public:
	SocketHandler(Socket * s, int mode,MessageHandler* m_handler,MaquinaEstados* maq,int id);
	virtual ~SocketHandler(void);

private:
	SocketHandler(void);
	Socket * _socket;
	string msgRemainder;
	MessageHandler* m_handler;
	MaquinaEstados* maq;
	int id;

protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __SOCKETHANDLER_H__