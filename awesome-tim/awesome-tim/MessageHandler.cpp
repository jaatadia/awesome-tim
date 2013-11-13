#include "MessageHandler.h"

MessageHandler::MessageHandler(int mode, MaquinaEstados * game, int id) : ConnectionManager(mode)
{
	this->game = game;
	this->id = id;
}

MessageHandler::~MessageHandler(void)
{
}