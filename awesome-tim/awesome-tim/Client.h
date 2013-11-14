#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "ClientSocket.h"
#include "CommunicationManager.h"
#include "SocketException.h"
#include "MaquinaEstados.h"
#include <iostream>

using namespace std;

class Client
{
public:
	Client(MaquinaEstados * juego,char* IP = "25.169.117.108");
	virtual ~Client(void);

private:
	CommunicationManager * commMgr;
};

#endif // __CLIENT_H__