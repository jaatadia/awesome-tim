#pragma once

#include "Message.h"

class FireBowMessage: public Message
{
public:
	FireBowMessage();
	FireBowMessage(string msg);
	~FireBowMessage(void);

	virtual string serialize();

	void setGunID(int id);
	void setProyectileID(int id);

	int getGunID();
	int getProyectileID();

private:
	int gunID;
	int proyectileID;
};
