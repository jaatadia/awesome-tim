#pragma once

#include "Superficie.h"
#include "EscalasDeEjes.h"

class Dibujable
{
public:
	virtual ~Dibujable(){};
	virtual void dibujar(Superficie* super)=0;
};
