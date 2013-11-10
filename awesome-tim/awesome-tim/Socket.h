#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include "Constantes.h"
#include "SocketException.h"
#include "Mutex.h"
#include "Lock.h"

#pragma comment(lib, "Ws2_32.lib")

class Socket {

public:
	Socket();
	Socket(SOCKET s);
	void write(std::string message);
	std::string read();
	~Socket();

private:
	void start();
	char buffer[TAM_BUFFER];
	Mutex _mutex;

protected:
	SOCKET _socket;
};

#endif // __SOCKET_H__