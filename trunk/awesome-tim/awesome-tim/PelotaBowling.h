#pragma once
#include "circulo.h"
#include "Constantes.h"
#include "Figura.h"

class PelotaBowling : public Figura
{
private:
	PelotaBowling(const char* id,Dimension* dim,bool flag):Figura(id,dim){};
public:
	PelotaBowling(double pos_X,double pos_Y,double angulo = 0):Figura(ID_PELOTABOWLING,new Circulo(RADIO_PELOTABOWLING,pos_X,pos_Y,angulo)){};
	~PelotaBowling(void){};

	virtual int getTipoFigura(){return PELOTABOWLING;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){return new PelotaBowling(ID.c_str(),dimension->clonar(),true);};

//	bool choqueConFigura(Figura* fig);
};
