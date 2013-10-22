#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "ActiveObject.h"
#include "ClientSocket.h"

class Client : public ActiveObject
{
public:
	Client(void);
	~Client(void);

private:
	ClientSocket * socket;
	void initThread();
	void run();
	void flushThread();
};

#endif // __CLIENT_H__