#include "Lock.h"

Lock::Lock(Mutex & mutex) : _mutex(mutex)
{
	try{
		_mutex.acquire();
	}catch(...){
	}
}

Lock::~Lock(void)
{
	try{
		_mutex.release();
	}catch(...){
	}
}
