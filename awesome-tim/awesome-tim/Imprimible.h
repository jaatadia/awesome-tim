#pragma once

#include "Superficie.h"

class Imprimible
{

public:
	virtual Superficie* getImpresion()=0;
};
