#pragma once

#include "ConnectionManager.h"
#include "MaquinaEstados.h"

class MessageHandler : public ConnectionManager
{
public:
	MessageHandler(int mode, MaquinaEstados * game, int id);
	~MessageHandler(void);

protected:
	MaquinaEstados * game;
	int id;
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
};
