#pragma once

#include "Superficie.h"

class Estado: public Fallable
{
public:
	virtual void onEvent(Superficie** sup)=0;
	virtual void onLoop()=0;
	virtual bool onRender(Superficie* sup)=0;
};
