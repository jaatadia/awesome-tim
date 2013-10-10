#pragma once
#include "Figura.h"
#include "VistaLinea.h"
#include "DLinea.h"

class VistaLinea;

class Linea: public Figura
{
private:
	Linea(DLinea* linea);
	bool puesto;

protected:
	Linea(const char* ID,double x1,double y1,double x2, double y2,double ancho = 1 );

public:
	Linea(double x1,double y1,double x2, double y2,double ancho = 1 );
	~Linea(void);

	virtual int getTipoFigura(){return LINEA;};
	//virtual int getTipoDimension(){return DLINEA;};   Y ESTO?? FIX
	virtual void setPunto1(double x1,double y1);
	virtual void setPunto2(double x2,double y2);
	virtual void setFigura1(Figura* fig);


	virtual Figura* clonar();
	virtual bool primerPuntoPuesto(){return puesto;};


	virtual bool esUnion(){
		return true;
	}
	virtual void desUnir(){
		fig1->desatarCorrea();
		fig2->desatarCorrea();
	}
};
