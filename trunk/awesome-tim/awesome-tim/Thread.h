#ifndef __THREAD_H__
#define __THREAD_H__

#define _WINSOCKAPI_
#include <windows.h>

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
