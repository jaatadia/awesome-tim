#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "Socket.h"
#include "ActiveObject.h"

class ClientHandler : public ActiveObject
{
public:
	ClientHandler(void);
	ClientHandler(Socket * s);
	virtual ~ClientHandler(void);

private:
	Socket * _socket;
protected:
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __CLIENTHANDLER_H__