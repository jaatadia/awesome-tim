#pragma once

#include "Dimension.h"

class Cuadrado: public Dimension
{
private:
	double ancho;
	double alto;

public:
	Cuadrado(double ancho,double alto);
	~Cuadrado(void);

	double getAncho();
	double getAlto();

};
