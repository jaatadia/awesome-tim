#pragma once
#include "Figura.h"
#include "VistaLinea.h"
#include "DLinea.h"

class VistaLinea;

class Linea: public Figura
{
protected:
	Linea(const char* ID,DLinea* linea);
	bool puesto,simple;

protected:
	Linea(const char* ID,bool doble,double x1,double y1,double x2, double y2,double ancho = 1 );

public:
	Linea(double x1,double y1,double x2, double y2,double ancho = 1 );
	~Linea(void);

	virtual int getTipoFigura(){return LINEA;};
	//virtual int getTipoDimension(){return DLINEA;};   Y ESTO?? FIX
	virtual void setPunto1(double x1,double y1);
	virtual void setPunto2(double x2,double y2);
	virtual void setFigura1(Figura* fig);

	virtual void posFigura1(double* x, double* y){fig1->posAtableCorrea(x,y);};
	virtual void posFigura2(double* x, double* y){fig2->posAtableCorrea(x,y);};


	virtual Figura* clonar();
	virtual bool primerPuntoPuesto(){return puesto;};


	virtual bool esUnion(){
		return true;
	}
	virtual void desUnir(){
		fig1->desatarCorrea();
		fig2->desatarCorrea();
	}

	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);

};
