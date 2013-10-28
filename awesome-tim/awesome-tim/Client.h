#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "ActiveObject.h"
#include "ClientSocket.h"

class Client : public ActiveObject
{
public:
	Client(void);
	virtual ~Client(void);

private:
	ClientSocket * socket;
protected:	
	virtual void initThread();
	virtual void run();
	virtual void flushThread();
};

#endif // __CLIENT_H__