#pragma once

#include "Superficie.h"
#include "EscalasDeEjes.h"

class Imprimible
{

public:
	virtual Superficie* getImpresion()=0;
	virtual Superficie* getImpresion(EscalasDeEjes* escalas)=0;
};
