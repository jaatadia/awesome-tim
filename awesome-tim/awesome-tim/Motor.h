#pragma once
#include "FiguraCompuesta.h"
#include "Cuadrado.h"

class Motor :
	public FiguraCompuesta
{
public:
	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	Motor(void);
	~Motor(void);
};
