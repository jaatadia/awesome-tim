#include "ActiveObject.h"

ActiveObject::ActiveObject() : finalizando(0), _thread(threadEntry, this)
{
}

void ActiveObject::kill() {
	finalizando++;
	flushThread();
	_thread.waitForDeath();
}

DWORD WINAPI ActiveObject::threadEntry(void * pArg)
{
	ActiveObject * pActive = (ActiveObject *) pArg;
	pActive->initThread();
	pActive->run();
	return 0;
}
