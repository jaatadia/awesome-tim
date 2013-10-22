#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

#include "Socket.h"

class ClientSocket : public Socket
{
public:
	ClientSocket(char * ip);
	~ClientSocket(void);
};

#endif // __CLIENTSOCKET_H__