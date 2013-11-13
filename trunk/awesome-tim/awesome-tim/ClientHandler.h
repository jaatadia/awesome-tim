#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "MessageHandler.h"
#include "Message.h"
#include "FilesMessage.h"
#include "IdMessage.h"
#include "Constantes.h"
#include <iostream>
#include <fstream>

using namespace std;

class ClientHandler : public MessageHandler
{
public:
	ClientHandler(int mode, MaquinaEstados * game, int id);
	virtual ~ClientHandler(void);

private:
	ClientHandler(void);

protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __CLIENTHANDLER_H__