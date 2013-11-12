#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__

#include "Socket.h"

class ServerSocket : public Socket
{
public:
	ServerSocket(void);
	~ServerSocket(void);
	Socket * acceptConnection();
};

#endif //__SERVERSOCKET_H__