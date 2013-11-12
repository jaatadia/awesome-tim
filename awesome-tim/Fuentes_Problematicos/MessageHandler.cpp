#include "MessageHandler.h"

MessageHandler::MessageHandler(int mode, MaquinaEstados * game) : ConnectionManager(mode)
{
	this->game = game;
}

MessageHandler::~MessageHandler(void)
{
}