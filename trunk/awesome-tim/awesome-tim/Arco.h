#pragma once

#include "Figura.h"
#include "Cuadrado.h"

class Arco: public Figura
{
private:
	Arco(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){}

public:
	Arco(double posX,double posY ,double angulo = 0):Figura(ID_ARCO,new Cuadrado(ANCHO_ARCO,ALTO_ARCO,posX,posY,angulo)){
	}
	
	~Arco(void){
	}

	virtual int getTipoFigura(){
		return ARCO;
	}

	virtual int getTipoDimension(){
		return CUADRADO;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		return false;
	}

	virtual Figura* clonar(){
		return new Arco(ID.c_str(),dimension->clonar(),true);
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}

	virtual bool rotable(){return true;}

};

