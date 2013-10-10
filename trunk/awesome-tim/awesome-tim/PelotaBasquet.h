#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"


class PelotaBasquet : public Figura
{
private:
	PelotaBasquet(const char* id,Dimension* dim,bool flag):Figura(id,dim){};

public:
	PelotaBasquet(double pos_X,double pos_Y,double angulo = 0):Figura(ID_PELOTABASQUET,new Circulo(RADIO_PELOTABASQUET,pos_X,pos_Y,angulo)){};
	~PelotaBasquet(void){};

	virtual int getTipoFigura(){return PELOTABASQUET;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){return new PelotaBasquet(ID.c_str(),dimension->clonar(),true);};

	bool choqueConFigura(Figura* fig);
};
