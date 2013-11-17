#pragma once

#include "Figura.h"
#include "Cuadrado.h"

class Bala: public Figura
{
public:
	double fuerzaX,fuerzaY;
private:
	bool atado;
	Bala(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		fuerzaX = fuerzaY = 0;
	}

public:
	Bala(double posX,double posY ,double angulo,double fuerzaX,double fuerzaY):Figura(ID_BALA,new Cuadrado(ANCHO_BALA,ALTO_BALA,posX,posY,angulo)){
		this->fuerzaX = fuerzaX;
		this->fuerzaY = fuerzaY;
	}
	
	~Bala(void){
	}

	virtual int getTipoFigura(){
		return BALA;
	}

	virtual int getTipoDimension(){
		return CUADRADO;
	}

	virtual Figura* clonar(){
		Bala* flecha = new Bala(ID.c_str(),dimension->clonar(),true);
		flecha->fuerzaX = fuerzaX;
		flecha->fuerzaY = fuerzaY;
		this->completarInteraccionesPosibles(flecha);
		return flecha;
	}

	virtual bool rompeHuevo(Dimension* dim){
		return true;
	}


	virtual bool pinchaGlobo(Dimension* dim){
		return true;
	}
};
