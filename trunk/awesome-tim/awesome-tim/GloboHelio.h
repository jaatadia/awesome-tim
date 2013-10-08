#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"

class GloboHelio : public Figura
{
private:
	GloboHelio(const char* id,Dimension* dim,bool flag):Figura(id,dim){};

public:
	GloboHelio(double pos_X,double pos_Y):Figura(ID_GLOBO,new Circulo(RADIO_GLOBOHELIO,pos_X,pos_Y,0)){};
	~GloboHelio(void){};

	virtual int getTipoFigura(){return GLOBOHELIO;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){return new GloboHelio(ID.c_str(),dimension->clonar(),true);};
};
