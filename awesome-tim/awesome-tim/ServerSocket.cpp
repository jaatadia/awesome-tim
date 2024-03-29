#include "ServerSocket.h"

ServerSocket::ServerSocket(void)
{
	struct addrinfo * resultado = NULL, * ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // Stream Socket
	hints.ai_protocol = IPPROTO_TCP; // TCP
	hints.ai_flags = AI_PASSIVE; // Bind

	if(getaddrinfo(NULL, PUERTO, &hints, &resultado))
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
		string mensaje = "Error al crear socket de lectura: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}

	if(bind(this->_socket, resultado->ai_addr, (int)resultado->ai_addrlen) == SOCKET_ERROR)
	{
		freeaddrinfo(resultado);
		closesocket(this->_socket);
		WSACleanup();
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al hacer bind del socket: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}

	freeaddrinfo(resultado);

	if(listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(this->_socket);
		WSACleanup();
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al intentar escuchar con el socket: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}
}

Socket * ServerSocket::acceptConnection()
{
	SOCKET incommingConnectionSocket = accept(this->_socket, NULL, NULL);
	if (incommingConnectionSocket == INVALID_SOCKET)
	{
		closesocket(this->_socket);
		WSACleanup();
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al aceptar socket entrante: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}
	Socket * aux = new Socket(incommingConnectionSocket);
	return aux;
}

ServerSocket::~ServerSocket(void)
{
}
