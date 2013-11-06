#ifndef __SERVER_H__
#define __SERVER_H__

#include "ActiveObject.h"
#include "ServerSocket.h"
#include "ClientHandler.h"
#include "SocketException.h"
#include <iostream>
#include <list>

using namespace std;

class Server : public ActiveObject
{
public:
	Server();
	~Server(void);
	void init();
	void stop();

private:
	std::list<ClientHandler * > clientRdrLst;
	std::list<ClientHandler * > clientWrtLst;
	ServerSocket * socket;
	void initThread();
	void run();
	void flushThread();
};

#endif // __SERVER_H__