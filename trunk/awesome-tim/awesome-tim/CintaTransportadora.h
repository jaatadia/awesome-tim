#pragma once

#include "FiguraCompuesta.h"
#include "Cuadrado.h"
#include "Constantes.h"

class CintaTransportadora : public FiguraCompuesta
{
public:
	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	CintaTransportadora(void);
	~CintaTransportadora(void);

	virtual int getTipoFigura(){return CINTATRANSPORTADORA;}
	virtual int getTipoDimension(){return CUADRADO;}
};
