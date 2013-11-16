#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "MessageHandler.h"
#include "Message.h"
#include "FilesMessage.h"
#include "IdMessage.h"
#include "ClientMessage.h"
#include "Constantes.h"
#include <iostream>
#include <fstream>

#include "SocketHandler.h"

using namespace std;

class ClientHandler : public MessageHandler
{
public:
	ClientHandler(int mode, MaquinaEstados * game, int id,SocketHandler* s_handler);
	virtual ~ClientHandler(void);

private:
	ClientHandler(void);
	SocketHandler* s_handler;

protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __CLIENTHANDLER_H__