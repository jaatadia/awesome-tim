#pragma once

#include "Superficie.h"

class Estado: public Fallable
{
public:
	virtual ~Estado(){};
	virtual bool onEvent(Ventana* ventana,Superficie** sup)=0;
	virtual void onLoop()=0;
	virtual bool onRender(Superficie* sup)=0;
	virtual void resume(){};
};
