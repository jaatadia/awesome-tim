#pragma once

#include "Figura.h"

#define TRIANGULO 1

class FiguraTriangular: public Figura
{
public:
	FiguraTriangular(const char* ID,double X, double Y, double angulo, double base,double altura);
	~FiguraTriangular(void);

	int getTipoDimension(){return TRIANGULO;};
};
