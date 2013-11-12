#pragma once

#include "Figura.h"
#include "Triangulo.h"


class Clavo: public Figura
{
private:
	Clavo(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){}

public:
	Clavo(double posX,double posY ,double angulo = 0):Figura(ID_CLAVO,new Triangulo(posX,posY,angulo,BASE_CLAVO,ALTURA_CLAVO)){
	}
	
	~Clavo(void){
	}

	virtual int getTipoFigura(){
		return CLAVO;
	}

	virtual int getTipoDimension(){
		return TRIANGULO;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		return true;
	}

	virtual Figura* clonar(){
		return new Clavo(ID.c_str(),dimension->clonar(),true);
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}

};
