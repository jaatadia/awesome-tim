#pragma once

#include "Figura.h"

class FiguraCuadrada: public Figura
{
public:
	FiguraCuadrada(const char* ID,double ancho,double alto,double X,double Y, double angulo);
	~FiguraCuadrada(void);

	int getTipoDimension(){return CUADRADO;};
	
	//Cuadrado* getDimension();
	
};
