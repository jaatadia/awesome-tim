#ifndef __LOCK_H__
#define __LOCK_H__

#include "Mutex.h"

class Lock
{
public:
    Lock(Mutex & mutex);
    ~Lock ();
private:
    Mutex & _mutex;
};

#endif // __LOCK_H__