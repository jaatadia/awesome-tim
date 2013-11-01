#pragma once

#include "Figura.h"

class Chinche: public Figura
{
private:
	Chinche(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){}

public:
	Chinche(double posX,double posY ,double angulo = 0):Figura(ID_CHINCHE,new Triangulo(posX,posY,angulo,BASE_CHINCHE,ALTURA_CHINCHE)){
	}
	
	~Chinche(void){
	}

	virtual int getTipoFigura(){
		return CHINCHE;
	}

	virtual int getTipoDimension(){
		return TRIANGULO;
	}

	virtual bool pinchaGlobo(){
		return true;
	}

	virtual Figura* clonar(){
		return new Chinche(ID.c_str(),dimension->clonar(),true);
	}

	virtual void shift(){
		this->setAngulo(dimension->getAngulo()+90);
	}
};
