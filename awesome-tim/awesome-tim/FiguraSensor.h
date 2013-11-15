#pragma once
#include "figura.h"
#include <list>

class FiguraSensor :
	public Figura
{
private:
	std::list<Figura*> figurasInteractuar;
	int ID;

public:
	FiguraSensor(double ancho,double alto,double posX,double posY,double angulo);
	~FiguraSensor(void);
	virtual int getTipoFigura();
	virtual int getTipoDimension();

	//FIX: espero que sean estas las q tengo q hacer false (?) 
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);
	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);
};
