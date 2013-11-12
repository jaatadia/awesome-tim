#include "Client.h"

Client::Client(MaquinaEstados * juego,char* IP)
{
	char* myIP;
	if (IP == NULL){
		myIP = "127.0.0.1";
	}else{
		myIP = IP;
	}

	try
	{
		this->commMgr = new CommunicationManager(new ClientSocket(myIP), juego);

	} catch (SocketException & sE)
	{
		cout << sE.what() << endl;
	}
}

Client::~Client(void)
{
}
