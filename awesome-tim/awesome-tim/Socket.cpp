#include "Socket.h"

Socket::Socket()
{
	this->start();
}

Socket::~Socket()
{

}

void Socket::start()
{
	WSADATA wsad;
	if(WSAStartup(MAKEWORD(2,2), &wsad))
	{
		throw SocketException("Error al inicializar Winsock");
	}
}

Socket::Socket(SOCKET s) : _socket(s)
{
  this->start();
};
