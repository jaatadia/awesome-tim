#ifndef __IDMESSAGE_H__
#define __IDMESSAGE_H__

#include "Message.h"
#include <sstream>

class IdMessage : public Message
{
public:
	IdMessage(string msg);
	IdMessage(void);
	virtual ~IdMessage(void);
	virtual string serialize();
	int getId();
	void setId(int id);

private:
	int id;
};

#endif // __IDMESSAGE_H__