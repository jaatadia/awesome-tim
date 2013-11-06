#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "ClientSocket.h"
#include "ServerHandler.h"

class Client
{
public:
	Client(void);
	virtual ~Client(void);

private:
	ClientSocket * socket;
	ServerHandler * rdrServer;
	ServerHandler * wrtServer;
};

#endif // __CLIENT_H__