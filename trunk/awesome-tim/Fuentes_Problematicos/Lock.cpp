#include "Lock.h"

Lock::Lock(Mutex & mutex) : _mutex(mutex)
{
    _mutex.acquire();
}

Lock::~Lock(void)
{
	_mutex.release();
}
