#include "ActiveObject.h"

ActiveObject::ActiveObject() : finalizando(0), _thread(threadEntry, this)
{
}

void ActiveObject::kill() {
	if(!finalizando){
		finalizando++;
		flushThread();
		_thread.waitForDeath();
	}
}

DWORD WINAPI ActiveObject::threadEntry(void * pArg)
{
	ActiveObject * pActive = (ActiveObject *) pArg;
	pActive->initThread();
	pActive->run();
	return 0;
}

int ActiveObject::getActiveState()
{
	return this->finalizando;
}

void ActiveObject::sleep(int milliseconds)
{
	this->_thread.sleep(milliseconds);
}