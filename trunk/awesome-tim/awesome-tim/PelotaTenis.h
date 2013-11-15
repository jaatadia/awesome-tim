#pragma once

#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"


class PelotaTenis : public Figura
{
private:
	PelotaTenis(const char* id,Dimension* dim,bool flag):Figura(id,dim){};

public:
	PelotaTenis(double pos_X,double pos_Y,double angulo = 0):Figura(ID_PELOTATENIS,new Circulo(RADIO_PELOTATENIS,pos_X,pos_Y,angulo)){};
	~PelotaTenis(void){};

	virtual int getTipoFigura(){return PELOTATENIS;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){
		Figura* pelota = new PelotaTenis(ID.c_str(),dimension->clonar(),true);
		this->completarInteraccionesPosibles(pelota);
		return pelota;
	};

//	bool choqueConFigura(Figura* fig);
	
	virtual int esAtableSoga(double x,double y){
		return 1;
	}
};
