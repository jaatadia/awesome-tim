#include "ClientSocket.h"

ClientSocket::ClientSocket(char * ip)
{
	struct addrinfo * resultado = NULL, * ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; // Stream Socket
	hints.ai_protocol = IPPROTO_TCP; // TCP

	if(getaddrinfo(ip, PUERTO, &hints, &resultado))
	{
		WSACleanup();
		throw SocketException("Error al usar getaddrinfo");
	}

	this->_socket = socket(resultado->ai_family, resultado->ai_socktype, resultado->ai_protocol);

	if(this->_socket == INVALID_SOCKET)
	{
		freeaddrinfo(resultado);
		WSACleanup();
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al crear socket de cliente: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}

	if(connect(this->_socket, resultado->ai_addr, (int)resultado->ai_addrlen) == SOCKET_ERROR)
	{
		freeaddrinfo(resultado);
		closesocket(this->_socket);
		WSACleanup();
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al hacer connect del socket: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}

	freeaddrinfo(resultado);
}

ClientSocket::~ClientSocket(void)
{
}
