#ifndef __SERVERHANDLER_H__
#define __SERVERHANDLER_H__

#include "ConnectionHandler.h"
#include "Message.h"
#include "Constantes.h"
#include <iostream>
#include <fstream>

class ServerHandler : public ConnectionHandler
{
public:
	ServerHandler(void);
	ServerHandler(Socket * s, int mode);
	virtual ~ServerHandler(void);

protected:
	virtual void update();
};

#endif // __SERVERHANDLER_H__