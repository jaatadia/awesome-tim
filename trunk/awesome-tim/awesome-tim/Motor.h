#pragma once
#include "FiguraCompuesta.h"
#include "Cuadrado.h"
#include "Constantes.h"

class Motor :
	public FiguraCompuesta
{
public:
	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	Motor(void);
	~Motor(void);

	virtual int getTipoFigura(){return MOTOR;}
	virtual int getTipoDimension(){return CUADRADO;}
};
