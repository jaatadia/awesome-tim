#pragma once

#include "Superficie.h"
#include "EscalasDeEjes.h"

class Imprimible
{

public:
	//virtual ~Imprimible(){};
	virtual Superficie* getImpresion()=0;
	virtual void dibujate(Superficie* sup,int xIni,int yIni){};
};
