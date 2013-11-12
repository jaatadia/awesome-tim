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

	void PrintIP(){
		char ac[80];
		if(gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
			return;
		}

		std::cout << "Host name is " << ac << "." << "\n";

		struct hostent *phe = gethostbyname(ac);

		for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
			struct in_addr addr;
			memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
			std::cout << "Address " << i << ": " << inet_ntoa(addr) << "\n";
		}
	}
};

#endif // __SERVER_H__