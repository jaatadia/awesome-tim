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
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al enviar datos desde el socket: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}
}

std::string Socket::read()
{
	int cantidadLeida = 0;
	std::string salida = "";
	cantidadLeida = recv(this->_socket, this->buffer, TAM_BUFFER, 0);
	if (cantidadLeida > 0)
	{
		for(int i = 0; i < cantidadLeida; i++)
		{
			salida += buffer[i];
		}
		salida = salida.substr(0,cantidadLeida);
	}
	else if (cantidadLeida == 0){
		throw SocketException("El servidor se encuentra lleno, intente mas tarde...");
	}
	else
	{
		std::stringstream id;
		id << WSAGetLastError();
		string mensaje = "Error al recibir datos desde el socket: ";
		mensaje.append(id.str());
		throw SocketException(mensaje);
	}
	return salida;
}