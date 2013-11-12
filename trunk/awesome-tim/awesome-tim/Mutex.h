#ifndef __MUTEX_H__
#define __MUTEX_H__

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif // _WINSOCKAPI_

#include <windows.h>

class Mutex
{
    friend class Lock;
public:
    Mutex();
    ~Mutex();
private:
    void acquire();
    void release();

    CRITICAL_SECTION _critSection;
};

#endif // __MUTEX_H__