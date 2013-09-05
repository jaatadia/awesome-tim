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
	char* dirImagen;
	VistaFigura* myVista;

public:
	Figura(char* dir,int angulo,double posX,double posY);
	~Figura(void);

	void dibujar(Superficie* super){};
};
