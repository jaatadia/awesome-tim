#ifndef __SERVER_H__
#define __SERVER_H__

#include "ActiveObject.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "CommunicationManager.h"
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
	ServerSocket * _socket;
	std::list<CommunicationManager *> commMgrLst;
	void initThread();
	void run();
	void flushThread();
};

#endif // __SERVER_H__