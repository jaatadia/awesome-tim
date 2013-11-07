#include "Socket.h"

Socket::Socket()
{
	this->start();
}

Socket::~Socket()
{
	closesocket(this->_socket);
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

void Socket::write(std::string message)
{
	int resultado = send(this->_socket, message.c_str(), message.size(), 0);
	if (resultado == SOCKET_ERROR) {
		closesocket(this->_socket);
		WSACleanup();
		throw SocketException("Error al enviar datos desde el socket: " + WSAGetLastError());
	}
}

std::string Socket::read()
{
	int cantidadLeida = 0;
	std::string salida = "";
	cantidadLeida = recv(this->_socket, this->buffer, TAM_BUFFER, 0);
	if (cantidadLeida > 0)
	{
		salida = this->buffer;
		salida = salida.substr(0,cantidadLeida);
	}
	else if (cantidadLeida == 0)
		printf("Fin mensaje\n");
	else
		throw SocketException("Error al recibir datos desde el socket: " + WSAGetLastError());
	return salida;
}