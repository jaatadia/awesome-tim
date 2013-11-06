#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "ConnectionHandler.h"
#include "Message.h"
#include "Constantes.h"
#include <iostream>
#include <fstream>

using namespace std;

class ClientHandler : public ConnectionHandler
{
public:
	ClientHandler(void);
	ClientHandler(Socket * s, int mode);
	virtual ~ClientHandler(void);

protected:
	virtual void update();
};

#endif // __CLIENTHANDLER_H__