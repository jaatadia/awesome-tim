#ifndef __ACTIVEOBJECT_H__
#define __ACTIVEOBJECT_H__

#include "Thread.h"

class ActiveObject
{
public:
	ActiveObject();
	virtual ~ActiveObject() {};
	void kill();
	int getActiveState();
	void sleep(int milliseconds);
protected:
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
	static DWORD WINAPI threadEntry(void * pArg);
	int finalizando;
	Thread _thread;
};

#endif // __ACTIVEOBJECT_H__
