#pragma once
#include "figura.h"

class Codo :
	public Figura
{
/*
	6- - -1- - -
	 - - - - - -
	 - - - -2- -
	 - - - - - -3
	 - - - - - -
	 -5- - - - -
	 - - - - - -
	 - - - - - -4
	^y
	|
	|----->x
*/

public:
	Codo(double posX,double posY,double angulo);
	~Codo(void);

	int getTipoFigura();
	int getTipoDimension();
	Figura* clonar();
	virtual double calcularAngulo(double x1,double y1,double x2,double y2); //inicial, final
	virtual double calcularAncho(double x1,double y1,double x2,double y2);
	virtual void calcularPuntosRotados(double* x1,double* y1,double* x2,double* y2,double* x3,double* y3,double* x4,double* y4,double* x5,double* y5,double* x6,double* y6);
	virtual bool rotable(){return true;}

private:
	virtual void calcularPuntosSinRotar(double* x1,double* y1,double* x2,double* y2,double* x3,double* y3,double* x4,double* y4,double* x5,double* y5,double* x6,double* y6);
};
