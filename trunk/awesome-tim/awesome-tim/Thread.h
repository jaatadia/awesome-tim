#include <windows.h>

#ifndef __THREAD_H__
#define __THREAD_H__

class Thread
{
public:
	Thread(DWORD (WINAPI * pFun)(void * pArg), void * pArg);
	~Thread();
	void resume();
	void waitForDeath();
private:
	HANDLE _handle;
	DWORD _tid;
};

#endif // __THREAD_H__
