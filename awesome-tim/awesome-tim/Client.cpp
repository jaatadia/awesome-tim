#include "Client.h"

Client::Client(void)
{
	try
	{
		this->commMgr = new CommunicationManager(new ClientSocket("127.0.0.1"), CLIENT_TYPE);

	} catch (SocketException & sE)
	{
		cout << sE.what() << endl;
	}
}

Client::~Client(void)
{
}
