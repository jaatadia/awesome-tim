#include "Client.h"

Client::Client(MaquinaEstados * juego,char* IP)
{
	try
	{
		this->commMgr = new CommunicationManager(new ClientSocket(IP), juego,false, -1);

	} catch (SocketException & sE)
	{
		cout << sE.what() << endl;
	}
}

Client::~Client(void)
{
}
