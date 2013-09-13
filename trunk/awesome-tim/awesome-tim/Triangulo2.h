#pragma once

#include "Dimension.h"

class Triangulo2: public Dimension
{
	double base;
	double altura;
	double x1,y1,x2,y2,x3,y3;
public:
	Triangulo2(double X, double Y, double angulo, double base,double altura);
	~Triangulo2(void);
	bool puntoPertenece(double X, double Y);
	double getAncho(void);
	double getAlto(void);

private:
	double enRecta(double x,double y,double x0,double y0,double x1,double y1);
};
