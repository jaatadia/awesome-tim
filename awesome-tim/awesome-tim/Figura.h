#pragma once


#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "Cambiable.h"
#include "VistaFigura.h"

class VistaFigura;

class Figura: public Dibujable,public Cambiable
{
public:
	friend class VistaFigura;

private:
	
	Dimension* dimension;
	Posicion pos;
	double angulo;
	const char* ID;
	VistaFigura* myVista;

public:
	Figura(const char* ID,Dimension* dim,int angulo,double posX,double posY);
	~Figura(void);

	void dibujar(Superficie* super);
};
