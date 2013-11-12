#include "Client.h"

Client::Client(MaquinaEstados * juego)
{
	try
	{
		this->commMgr = new CommunicationManager(new ClientSocket("127.0.0.1"), juego);

	} catch (SocketException & sE)
	{
		cout << sE.what() << endl;
	}
}

Client::~Client(void)
{
}
