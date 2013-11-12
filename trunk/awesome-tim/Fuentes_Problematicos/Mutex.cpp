#include "Mutex.h"

Mutex::Mutex(void)
{
	InitializeCriticalSection(& _critSection);
}

Mutex::~Mutex(void)
{
	DeleteCriticalSection(& _critSection);
}

void Mutex::acquire()
{
    EnterCriticalSection(& _critSection);
}

void Mutex::release()
{
    LeaveCriticalSection(& _critSection);
}