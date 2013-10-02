#pragma once

#include "FiguraCompuesta.h"
#include "Cuadrado.h"

class CintaTransportadora : public FiguraCompuesta
{
public:
	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	CintaTransportadora(void);
	~CintaTransportadora(void);
};
