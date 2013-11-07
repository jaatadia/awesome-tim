#ifndef __CONNECTIONHANDLER_H__
#define __CONNECTIONHANDLER_H__

#include "Socket.h"
#include "ActiveObject.h"
#include "Message.h"
#include "GreetingMessage.h"
#include "FilesMessage.h"
#include "EventMessage.h"
#include "GoodbyeMessage.h"
#include "Constantes.h"
#include "Mutex.h"
#include "Lock.h"
#include <iostream>
#include <list>
#include <stdlib.h>

class ConnectionHandler : public ActiveObject
{
public:
	ConnectionHandler(void);
	ConnectionHandler(Socket * s, int mode);
	virtual ~ConnectionHandler(void);

private:
	Socket * _socket;
	string msgRemainder;

protected:
	std::list<Message * > outputMsgLst;
	std::list<Message * > inputMsgLst;
	int state;
	int mode;
	Mutex _mutex;
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
	virtual void update() = 0;
	void setState(int state);
	void setMode(int mode);
	int getState();
	int getMode();
};

#endif // __CONNECTIONHANDLER_H__