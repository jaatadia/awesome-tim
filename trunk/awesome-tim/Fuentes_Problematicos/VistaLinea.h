#pragma once

#include "Linea.h"
#include "VistaFigura.h"
#include "Superficie.h"

class Linea;

class VistaLinea: public VistaFigura
{
private:
	Linea* linea;
	bool simple;

public:
	VistaLinea(Linea* lin,bool simple = true);
	~VistaLinea(void);
	
	void dibujar(Superficie* canvas);
};
