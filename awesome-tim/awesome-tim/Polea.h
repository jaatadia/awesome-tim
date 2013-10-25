#pragma once

#include "Figura.h"
#include "Box2D/Box2D.h"
#include "Soga.h"

class Polea: public Figura
{
public:
	int numIzq,numDer;
	b2Body* miCuerpo,* cuerpoIzq,* cuerpoDer;
	Soga* sogaDer,* sogaIzq;
	b2Joint* joint;

protected:
	bool atadoIzq,atadoDer;
	Polea(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		atadoIzq = atadoDer = false;
	};

public:
	Polea(double pos_X,double pos_Y,double angulo = 0):Figura(ID_POLEA,new Circulo(RADIO_POLEA,pos_X,pos_Y,angulo)){
		atadoIzq = atadoDer = false;
	};
	~Polea(void){};

	virtual int getTipoFigura(){return POLEA;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){
		return new Polea(ID.c_str(),dimension->clonar(),true);
	};

	virtual int esAtableSoga(double x,double y){
		if ((x<= dimension->getX())&&(!atadoIzq)){
			return 1;
		}else if (!atadoDer){
			return 2;
		}else{
			return -1;
		}
	}
	
	virtual void posAtableSoga(int numero,double* x,double* y){
		double desfasaje = 0;
		if(numero == 1){
			desfasaje = -(((Circulo*)dimension)->getRadio()-1);
		}else{
			desfasaje = ((Circulo*)dimension)->getRadio()-1;
		}
		*x = this->getDimension()->getX()+desfasaje;
		*y = this->getDimension()->getY();
	}

	virtual void atarSoga(int numero){
		if(numero == 1){
			atadoIzq = true;
		}else{
			atadoDer = true;
		}
	};
	virtual void desatarSoga(int numero){
		if(numero == 1){
			atadoIzq = false;
		}else{
			atadoDer = false;
		}
	};

	virtual Figura* getIzq(Polea* poleaPadre);
	virtual Figura* getDer(Polea* poleaPadre);
	virtual Polea* getPolIzq(Polea* poleaPadre,int* num);
	virtual Polea* getPolDer(Polea* poleaPadre,int* num);
	virtual void marcarSogas(bool flag,Polea* padre = NULL);
	virtual void setJoint(b2Joint* joint,Polea* padre = NULL);
};
