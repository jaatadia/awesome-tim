#pragma once

#include "Posicion.h"

class Dimension: public Posicion
{
private:
	double angulo;

public:
	Dimension(double X, double Y,double angulo):Posicion(X,Y){
		this->angulo=angulo;
	};

	virtual double getAncho()=0;
	virtual double getAlto()=0;

	virtual double getAngulo(){
		return angulo;
	};

	virtual bool puntoPertenece(double X, double Y)=0;
};
