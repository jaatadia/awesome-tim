#pragma once

#include "Terreno.h"
class Terrreno;

class MaquinaEstados
{
public:
	//virtual ~MaquinaEstados(){};
	virtual void salir()=0;
	virtual void editor()=0;
	virtual void play(Terreno* ter)=0;
};
