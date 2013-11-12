#pragma once

#include "Imagen.h"
#include "Figura.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"

class Figura;

class VistaFigura{

protected:
	Figura* fig;
	Imagen* orig;
	Imagen* rotada;
	bool modoGreedy;
	int escalaAnterior;

public:
	VistaFigura(Figura* fig);
	virtual ~VistaFigura();
	//dibuja la figura tomando su posicion como pixels
	virtual void dibujarEnPixel(Superficie* canvas);
	//dibuja la figura tomando su posicion como unidades logicas , probablemente siempre hay que usar este
	virtual void dibujar(Superficie* canvas);
	virtual void dibujar(Superficie* canvas,int xIni,int yIni);

protected:
	virtual void redraw();
	VistaFigura(){};

};


