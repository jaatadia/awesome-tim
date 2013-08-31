#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"

class Comandos: public Imprimible,Validable,Cambiable
{
public:
	Comandos(void);
	~Comandos(void);
};
