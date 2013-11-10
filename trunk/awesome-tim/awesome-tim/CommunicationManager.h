#ifndef __COMMUNICATIONMANAGER_H__
#define __COMMUNICATIONMANAGER_H__

#include "MessageHandler.h"
#include "SocketHandler.h"
#include "Socket.h"
#include "ClientHandler.h"
#include "ServerHandler.h"
#include "ActiveObject.h"

class CommunicationManager : public ActiveObject
{
public:
	CommunicationManager(Socket * socket, int type);
	~CommunicationManager(void);

private:
	MessageHandler * messageReader;
	MessageHandler * messageWriter;
	SocketHandler * socketReader;
	SocketHandler * socketWriter;
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __COMMUNICATIONMANAGER_H__