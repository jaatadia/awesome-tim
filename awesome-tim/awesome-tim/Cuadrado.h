#pragma once

#include "Dimension.h"
#include "Recta.h"
#include "Constantes.h"
#include <math.h>

/*

 vert2*-----*vert1
      |     |
	  |     |
	  |     |
 vert3*-----*vert4

*/

//En realidad tambien es un rectangulo.

class Cuadrado: public Dimension
{
private:
	double ancho;
	double alto;

	Posicion vertice1,vertice2,vertice3,vertice4;

public:
	Cuadrado(double ancho,double alto,double X,double Y, double angulo);
	~Cuadrado(void);

	double getAncho();
	double getAlto();
	
	bool puntoPertenece(double X, double Y);
	bool intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2);

	virtual int getTipoDimension(){return CUADRADO;}
	Dimension* clonar();
};
