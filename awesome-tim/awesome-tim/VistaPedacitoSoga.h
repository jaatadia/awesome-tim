#pragma once

#include "PedacitoSoga.h"
#include "VistaFigura.h"

class PedacitoSoga;

class VistaPedacitoSoga: public VistaFigura
{
private:
	PedacitoSoga* pedacito;

public:
	VistaPedacitoSoga(PedacitoSoga* pedacito);
	
	~VistaPedacitoSoga(void){}

	void dibujar(Superficie* canvas);
};
