#ifndef __CONNECTIONMANAGER_H__
#define __CONNECTIONMANAGER_H__

#include "ActiveObject.h"
#include "Message.h"
#include "Mutex.h"
#include "Lock.h"
#include "Socket.h"
#include "SocketException.h"
#include <list>

using namespace std;

class ConnectionManager : public ActiveObject
{
public:
	ConnectionManager(void);
	ConnectionManager(int mode);
	virtual ~ConnectionManager(void);
	int getState();
	int getMode();
	void pushInputMessage(Message * msg);
	Message * getInputMessage();
	void pushOutputMessage(Message * msg);
	Message * getOutputMessage();

private:
	std::list<Message * > outputMsgLst;
	std::list<Message * > inputMsgLst;
	int state;
	int mode;
	Mutex _mutex;

protected:
	virtual void initThread() = 0;
	virtual void run() = 0;
	virtual void flushThread() = 0;
	void setState(int state);
	void setMode(int mode);

};

#endif // __CONNECTIONMANAGER_H__