#include "ClientHandler.h"

ClientHandler::ClientHandler(void)
{
	this->_thread.resume();
}

ClientHandler::ClientHandler(Socket * s)
{
	this->_socket = s;
	this->_thread.resume();
}

ClientHandler::~ClientHandler(void)
{
}

void ClientHandler::initThread()
{

}

void ClientHandler::flushThread()
{

}

void ClientHandler::run()
{

}