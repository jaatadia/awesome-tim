#pragma once

#include "FireBowMessage.h"

class FireShotgunMessage: public FireBowMessage
{
public:
	FireShotgunMessage(void);
	FireShotgunMessage(string msg);
	~FireShotgunMessage(void);
};
