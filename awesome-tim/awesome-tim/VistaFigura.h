#pragma once

#include "Imagen.h"
#include "Figura.h"
#include "EscalasDeEjes.h"

class Figura;

class VistaFigura{

private:
	Figura* fig;
	Imagen* img;

public:
	VistaFigura(Figura* fig);
	~VistaFigura(void);
	//dibuja la figura tomando su posicion como pixels
	void dibujarEnPixel(Superficie* canvas,EscalasDeEjes* unidadesLogicas);
	//dibuja la figura tomando su posicion como unidades logicas , probablemente siempre hay que usar este
	void dibujar(Superficie* canvas,EscalasDeEjes* unidadesLogicas);

private:
	void redraw(EscalasDeEjes* unidadesLogicas);

};


