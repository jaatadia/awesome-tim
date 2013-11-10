#pragma once

#include "ConnectionManager.h"

class MessageHandler : public ConnectionManager
{
public:
	MessageHandler(void);
	MessageHandler(int mode);
	~MessageHandler(void);

protected:
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
};
