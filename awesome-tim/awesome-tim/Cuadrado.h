#pragma once

#include "Dimension.h"
#include "Recta.h"
#include "Constantes.h"
#include <math.h>

/*
      vert1
        *
       / \
 vert2*   *vert4
       \ /
        *
       vert3

Girado 45 grados en sentido antihorario.
*/

class Cuadrado: public Dimension
{
private:
	double ancho;
	double alto;

	double diagonal;
	double anguloDiagonal;
	//guardados respecto al centro
	Posicion vertice1,vertice2,vertice3,vertice4;

public:
	Cuadrado(double ancho,double alto,double X,double Y, double angulo);
	~Cuadrado(void);

	double getAncho();
	double getAlto();

	void setAngulo(double ang);
	
	bool puntoPertenece(double X, double Y);

	virtual int getTipoDimension(){return CUADRADO;}
	Dimension* clonar();
};
