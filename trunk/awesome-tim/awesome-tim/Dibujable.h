#pragma once

#include "Superficie.h"
#include "EscalasDeEjes.h"

class Dibujable
{
public:
	virtual void dibujar(Superficie* super,EscalasDeEjes* escalas)=0;
};
