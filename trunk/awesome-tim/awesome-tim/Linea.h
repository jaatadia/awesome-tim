#pragma once
#include "Figura.h"

class Linea: public Figura
{
private:
	double x1,y1,x2,y2,ancho;

public:
	Linea(double x1,double y1,double x2, double y2,double ancho = 1 );
	~Linea(void);

	virtual int getTipoFigura(){return LINEA;};
	virtual void setPunto1(double x1,double y1);
	virtual void setPunto2(double x2,double y2);

	virtual Figura* clonar();
};
