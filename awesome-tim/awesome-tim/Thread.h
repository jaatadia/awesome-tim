#ifndef __THREAD_H__
#define __THREAD_H__

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif // _WINSOCKAPI_

#include <windows.h>

class Thread
{
public:
	Thread(DWORD (WINAPI * pFun)(void * pArg), void * pArg);
	~Thread();
	void resume();
	void waitForDeath();
	void sleep(int milliseconds);
private:
	HANDLE _handle;
	DWORD _tid;
};

#endif // __THREAD_H__
