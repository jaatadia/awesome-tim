#pragma once

#include "Posicion.h"
#include "Segmento.h"

class Dimension: public Posicion
{
protected:
	double angulo; // de 0 a 360 !!

public:
	Dimension(double X, double Y,double angulo):Posicion(X,Y){
		this->angulo=angulo;
	};

	virtual double getAncho()=0;
	virtual double getAlto()=0;

	virtual double getAngulo(){
		return angulo;
	};
	virtual void setAngulo(double ang){
		this->angulo=ang;
	};

	virtual bool puntoPertenece(double X, double Y)=0;
	//la haria abstracta pero ahora mismo no se que dimensiones van a quedar, asi que implemento en poligono y circulo
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2){ return true;};
};
