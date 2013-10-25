#pragma once
#include "Polea.h"

class Aro: public Polea
{
public:
	Aro(double pos_X,double pos_Y,double angulo = 0):Polea(ID_ARO,new Circulo(RADIO_ARO,pos_X,pos_Y,angulo),true){
	};

	~Aro(void){
	}

	virtual void posAtableSoga(int numero,double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY();
	}
};
