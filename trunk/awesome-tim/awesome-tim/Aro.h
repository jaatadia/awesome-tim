#pragma once
#include "Polea.h"

class Aro: public Figura
{
private:
	bool atado;
	Aro(const char* ID,Dimension* dim,bool flag):Figura(ID,dim){
		atado = false;
	}

public:
	Aro(double pos_X,double pos_Y,double angulo = 0):Figura(ID_ARO,new Circulo(RADIO_ARO,pos_X,pos_Y,angulo),true){
		atado = false;
	};

	~Aro(void){
	}

	virtual void posAtableSoga(int numero,double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY();
	}

	virtual Figura* clonar(){
		Figura* aro = new Aro(ID.c_str(),dimension->clonar(),true);
		this->completarInteraccionesPosibles(aro);
		return aro;
	}

	virtual int getTipoFigura(){
		return ARO;
	}

	virtual int getTipoDimension(){
		return CIRCULO;
	}

	virtual int esAtableSoga(double x,double y){
		if(!atado) return 1;
		else return -1;
	}

	virtual void atarSoga(int numero){
		atado = true;
	}

	virtual void desatarSoga(int numero){
		atado = false;
	}
};
