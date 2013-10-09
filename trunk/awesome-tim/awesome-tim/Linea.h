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

public:
	Figura *fig1,*fig2;
	Linea(double x1,double y1,double x2, double y2,double ancho = 2 );
	~Linea(void);

	virtual int getTipoFigura(){return LINEA;};
	virtual void setPunto1(double x1,double y1);
	virtual void setPunto2(double x2,double y2);
	virtual void setPunto1(Figura* fig);
	virtual void setPunto2(Figura* fig);

	virtual Figura* clonar();
	virtual bool primerPuntoPuesto(){return puesto;};

	virtual Figura* getFigura1(){return fig1;};
	virtual Figura* getFigura2(){return fig2;};
};
