#ifndef __SERVER_H__
#define __SERVER_H__

#include "ActiveObject.h"
#include "ServerSocket.h"
#include "SocketException.h"
#include "CommunicationManager.h"
#include "MaquinaEstados.h"
#include <iostream>
#include <list>

using namespace std;

class Server : public ActiveObject
{
public:
	Server(MaquinaEstados * juego);
	~Server(void);
	void stop();

private:
	ServerSocket * _socket;
	std::list<CommunicationManager *> commMgrLst;
	MaquinaEstados * juego;
	void initThread();
	void run();
	void flushThread();
};

#endif // __SERVER_H__