#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"

class Terreno: public Imprimible,Validable,Cambiable
{
public:
	Terreno(void);
	~Terreno(void);


};
