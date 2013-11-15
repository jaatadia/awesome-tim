#pragma once

#include "Figura.h"

class Yunque: public Figura
{
private:
	Yunque(const char* id,Dimension* dim,bool flag):Figura(id,dim){};

public:
	Yunque(double pos_X,double pos_Y,double angulo = 0):Figura(ID_YUNQUE,new Cuadrado(ANCHO_YUNQUE,ALTO_YUNQUE,pos_X,pos_Y,angulo))
	{
	};

	~Yunque(void){};

	virtual int getTipoFigura(){return YUNQUE;}
	virtual int getTipoDimension(){return CUADRADO;}

	Figura* clonar(){
		Figura* yunque = new Yunque(ID.c_str(),dimension->clonar(),true);
		this->completarInteraccionesPosibles(yunque);
		return yunque;
	};

	virtual int esAtableSoga(double x,double y){
		return 1;
	}

};