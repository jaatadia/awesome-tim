#include "FireShotgunMessage.h"

FireShotgunMessage::FireShotgunMessage(void)
{
	this->type = MSG_TYPE_FIRE_SHOTGUN;
	this->valid = MSG_VALID;
}

FireShotgunMessage::FireShotgunMessage(string msg):FireBowMessage(msg)
{
	this->type = MSG_TYPE_FIRE_SHOTGUN;
	this->valid = MSG_VALID;
}

FireShotgunMessage::~FireShotgunMessage(void)
{
}
