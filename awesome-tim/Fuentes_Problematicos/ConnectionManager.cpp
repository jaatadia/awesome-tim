#include "ConnectionManager.h"

ConnectionManager::ConnectionManager(void)
{
	setState(0);
	this->_thread.resume();
}

ConnectionManager::ConnectionManager(int mode)
{
	setState(0);
	setMode(mode);
	this->_thread.resume();
}

ConnectionManager::~ConnectionManager(void)
{
}

void ConnectionManager::setState(int state)
{
	Lock lock(this->_mutex);
	this->state = state;
}

void ConnectionManager::setMode(int mode)
{
	Lock lock(this->_mutex);
	this->mode = mode;
}

int ConnectionManager::getState()
{
	Lock lock(this->_mutex);
	return this->state;
}

int ConnectionManager::getMode()
{
	Lock lock(this->_mutex);
	return this->mode;
}

void ConnectionManager::pushInputMessage(Message * msg)
{
	Lock lock(this->_mutex);
	this->inputMsgLst.push_back(msg);
}

void ConnectionManager::pushOutputMessage(Message *msg)
{
	Lock lock(this->_mutex);
	this->outputMsgLst.push_back(msg);
}

Message * ConnectionManager::getInputMessage()
{
	Lock lock(this->_mutex);
	Message * msg = NULL;
	if(!this->inputMsgLst.empty())
	{
		msg = (Message *) this->inputMsgLst.front();
		this->inputMsgLst.pop_front();
	}
	return msg;
}

Message * ConnectionManager::getOutputMessage()
{
	Lock lock(this->_mutex);
	Message * msg = NULL;
	if(!this->outputMsgLst.empty())
	{
		msg = (Message *) this->outputMsgLst.front();
		this->outputMsgLst.pop_front();
	}
	return msg;
}
