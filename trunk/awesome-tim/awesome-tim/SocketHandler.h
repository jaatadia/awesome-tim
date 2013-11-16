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

class SocketHandler : public ConnectionManager
{
public:
	SocketHandler(Socket * s, int mode,MessageHandler* m_handler);
	virtual ~SocketHandler(void);

private:
	SocketHandler(void);
	Socket * _socket;
	string msgRemainder;
	MessageHandler* m_handler;

protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __SOCKETHANDLER_H__