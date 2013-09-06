#pragma once

#include "dimension.h"

class Circulo : public Dimension
{
private:
	double radio;
public:
	Circulo(double radio,double pos_X,double pos_Y,double angulo);
	~Circulo(void);
	double getAncho();
	double getAlto();
	bool puntoPertenece(double pos_X, double pos_Y);
}