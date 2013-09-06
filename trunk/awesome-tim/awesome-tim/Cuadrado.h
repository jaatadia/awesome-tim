#pragma once

#include "Dimension.h"

class Cuadrado: public Dimension
{
private:
	double ancho;
	double alto;

public:
	Cuadrado(double ancho,double alto,double X,double Y, double angulo);
	~Cuadrado(void);

	double getAncho();
	double getAlto();

	bool puntoPertenece(double X, double Y);
};
