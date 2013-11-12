#pragma once
#include "Queso.h"
#include "Constantes.h"
#include "Triangulo.h"
#include "Figura.h"

class Queso : public Figura{

public:
	Queso(double pos_X,double pos_Y):Figura(ID_QUESO,new Triangulo(pos_X, pos_Y, 0, BASE_QUESO,ALTO_QUESO)){};

	~Queso(void){};

	virtual int getTipoFigura(){return QUESO;}
	virtual int getTipoDimension(){return TRIANGULO;}
	
	Figura* clonar(){
		return new Queso(this->getDimension()->getX(),this->getDimension()->getY());
	}

};