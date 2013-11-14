#ifndef __COMMUNICATIONMANAGER_H__
#define __COMMUNICATIONMANAGER_H__

#include "MessageHandler.h"
#include "ClientMessage.h"
#include "SocketHandler.h"
#include "Socket.h"
#include "ClientHandler.h"
#include "ServerHandler.h"
#include "ActiveObject.h"
#include "MaquinaEstados.h"
#include "MEstadosCliente.h"

class CommunicationManager : public ActiveObject
{
public:
	CommunicationManager(Socket * socket, MaquinaEstados * game,bool server, int id);
	~CommunicationManager(void);

private:
	bool server;
	int ID;
	MessageHandler * messageReader;
	MessageHandler * messageWriter;
	SocketHandler * socketReader;
	SocketHandler * socketWriter;
	MaquinaEstados * game;
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __COMMUNICATIONMANAGER_H__