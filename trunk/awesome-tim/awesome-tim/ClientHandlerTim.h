#pragma once
#include "clienthandler.h"

class ClientHandlerTim :
	public ClientHandler
{
public:
	ClientHandlerTim(void);
	~ClientHandlerTim(void);

protected:
	virtual void initThread(){};
	virtual void run(){};
	virtual void flushThread(){};
};
