#pragma once

#include "dimension.h"
#include "Constantes.h"

class Circulo : public Dimension
{
private:
	double radio;
public:
	Circulo(double radio,double pos_X,double pos_Y,double angulo);
	~Circulo(void);
	double getAncho();
	double getAlto();
	double getRadio();
	bool puntoPertenece(double pos_X, double pos_Y);

	bool intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2);

	virtual int getTipoDimension(){return CIRCULO;}
	Dimension* clonar();
};
