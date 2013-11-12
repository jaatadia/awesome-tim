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
	virtual void setAncho(double nuevoLargo);

	virtual bool choqueConDimension(Dimension* dim);

	virtual Dimension* rotarDimension(double Xrot, double yRot, double angulo);

	void setX1(double x){vertice1.setX(x);};
	void setX2(double x){vertice2.setX(x);};
	void setX3(double x){vertice3.setX(x);};
	void setX4(double x){vertice4.setX(x);};
	
	void setY1(double y){vertice1.setY(y);};
	void setY2(double y){vertice2.setY(y);};
	void setY3(double y){vertice3.setY(y);};
	void setY4(double y){vertice4.setY(y);};


	double getX1(){return vertice1.getX();};
	double getX2(){return vertice2.getX();};
	double getX3(){return vertice3.getX();};
	double getX4(){return vertice4.getX();};

	double getY1(){return vertice1.getY();};
	double getY2(){return vertice2.getY();};
	double getY3(){return vertice3.getY();};
	double getY4(){return vertice4.getY();};
		
};
