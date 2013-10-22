#pragma once

#include "Figura.h"
#include "VistaPedacitoSoga.h"
#include "Box2D/Box2d.h"

class VistaPedacitoSoga;

class PedacitoSoga: public Figura
{
public:

	double px1,px2,py1,py2;
	double centroX,centroY;
	double longitud;
	b2Joint* jointSoga;
	
	b2Joint* jointIzq;
	Figura* pedacitoIzq;
	b2Joint* jointDer;
	Figura* pedacitoDer;

	PedacitoSoga(double centroX,double centroY,double largo,double angulo);
	
	~PedacitoSoga(void){}

	void setX(double x);
	void setY(double y);
	void setAngulo(double angulo);

	int getTipoFigura(){
		return PEDACITOSOGA;
	}
};
