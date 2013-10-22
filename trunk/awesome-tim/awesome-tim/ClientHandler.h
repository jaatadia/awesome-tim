#ifndef __CLIENTHANDLER_H__
#define __CLIENTHANDLER_H__

#include "Socket.h"
#include "ActiveObject.h"

class ClientHandler : public ActiveObject
{
public:
	ClientHandler(void);
	ClientHandler(Socket * s);
	~ClientHandler(void);

private:
	Socket * _socket;
	void initThread();
	void run();
	void flushThread();
};

#endif // __CLIENTHANDLER_H__