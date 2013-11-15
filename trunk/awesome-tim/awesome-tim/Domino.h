#pragma once
#include "Cuadrado.h"
#include "Constantes.h"
#include "Figura.h"

class Domino : public Figura{

public:
	Domino(double pos_X,double pos_Y, const char* id = ID_FICHA_DOMINO):Figura(id,new Cuadrado(ANCHO_DOMINO,ALTO_DOMINO,pos_X,pos_Y,0)){};
	~Domino(void){};

	virtual int getTipoFigura(){return DOMINO;}
	virtual int getTipoDimension(){return CUADRADO;}
	
	Figura* clonar(){
		Figura* domino = new Domino(this->getDimension()->getX(),this->getDimension()->getY(), ID_DOMINO);
		this->completarInteraccionesPosibles(domino);
		return domino;
	}

};