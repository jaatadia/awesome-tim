#include <windows.h>
#include "Thread.h"

#ifndef __ACTIVEOBJECT_H__
#define __ACTIVEOBJECT_H__

class ActiveObject
{
public:
	ActiveObject();
	virtual ~ActiveObject() {};
	void kill();
protected:
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
	static DWORD WINAPI threadEntry(void * pArg);
	int _isDying;
	Thread _thread;
};

#endif // __ACTIVEOBJECT_H__
