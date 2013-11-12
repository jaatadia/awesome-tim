#pragma once

#include "Superficie.h"
#include "Imagen.h"
#include "Figura.h"

class VistaFiguraEstatica
{
private:
	const char* ID;
	Figura* fig;
	Imagen* rotada;
	int escalaAnterior;
public:
	VistaFiguraEstatica(Figura* fig, const char *ID);
	~VistaFiguraEstatica(void);

	void dibujar(Superficie* sup);
private:
	void redraw();
};
