#pragma once

#include "Linea.h"
#include "VistaFigura.h"
#include "Superficie.h"

class Linea;

class VistaLinea: public VistaFigura
{
private:
	Linea* linea;

public:
	VistaLinea(Linea* lin);
	~VistaLinea(void);
	
	void dibujar(Superficie* canvas);
};
