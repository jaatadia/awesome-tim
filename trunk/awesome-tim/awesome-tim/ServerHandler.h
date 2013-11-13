#ifndef __SERVERHANDLER_H__
#define __SERVERHANDLER_H__

#include "MessageHandler.h"
#include "Message.h"
#include "FilesMessage.h"
#include "IdMessage.h"
#include "Constantes.h"
#include "MEstadosCliente.h"
#include <iostream>
#include <fstream>

class ServerHandler : public MessageHandler
{
public:
	ServerHandler(int mode, MaquinaEstados * game, int id);
	virtual ~ServerHandler(void);

private:
	ServerHandler(void);

protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __SERVERHANDLER_H__