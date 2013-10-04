#pragma once

#include "Imagen.h"
#include "Figura.h"
#include "EscalasDeEjes.h"

class Figura;

class VistaFigura{

private:
	Figura* fig;
	Imagen* orig;
	Imagen* rotada;
	bool modoGreedy;
	int escalaAnterior;

public:
	VistaFigura(Figura* fig);
	~VistaFigura();
	//dibuja la figura tomando su posicion como pixels
	void dibujarEnPixel(Superficie* canvas);
	//dibuja la figura tomando su posicion como unidades logicas , probablemente siempre hay que usar este
	void dibujar(Superficie* canvas);
	void dibujar(Superficie* canvas,int xIni,int yIni);

private:
	void redraw();

};


