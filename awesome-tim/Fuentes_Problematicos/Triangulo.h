#pragma once

#include "Dimension.h"
#include "Constantes.h"

class Triangulo: public Dimension
{
	double base;
	double altura;
	double x1,y1,x2,y2,x3,y3;
public:
	Triangulo(double X, double Y, double angulo, double base,double altura);
	~Triangulo(void);
	bool puntoPertenece(double X, double Y);
	double getAncho(void);
	double getAlto(void);
	virtual int getTipoDimension(){return TRIANGULO;}
	Dimension* clonar();

	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual bool choqueConDimension(Dimension* dim);
	virtual Dimension* rotarDimension(double Xrot, double yRot, double angulo);

private:
	double enRecta(double x,double y,double x0,double y0,double x1,double y1);
};
