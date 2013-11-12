#pragma once

#include "ConnectionManager.h"
#include "MaquinaEstados.h"

class MessageHandler : public ConnectionManager
{
public:
	MessageHandler(int mode, MaquinaEstados * game);
	~MessageHandler(void);

protected:
	MaquinaEstados * game;
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
};
