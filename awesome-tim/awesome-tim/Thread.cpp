#include "Thread.h"

Thread::Thread(DWORD (WINAPI * pFun)(void * pArg), void * pArg)
{
	_handle = CreateThread(0, 0, pFun, pArg, CREATE_SUSPENDED, &_tid);
}

Thread::~Thread()
{
	CloseHandle(_handle);
}

void Thread::resume()
{
	ResumeThread(_handle);
}

void Thread::waitForDeath()
{
	WaitForSingleObject(_handle, 2000);
}
