#pragma once

#include "figura.h"
#include "Constantes.h"
#include "Circulo.h"

class Engranaje : public Figura
{
protected:
	Engranaje(const char* id,Dimension* dim,bool flag):Figura(id,dim){};
	double radio1;

public:

	b2Joint* joint;

	Engranaje(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Figura(ID_ENGRANAJE,new Circulo(radio1,pos_X,pos_Y,angulo)){
		
		if (radio1< RADIO_MINENGRANAJE)	this->radio1 = RADIO_MINENGRANAJE;
		else if (radio1 > RADIO_MAXENGRANAJE) this->radio1 = RADIO_MAXENGRANAJE;
		else this->radio1 = radio1;

		((Circulo*)(this->getDimension()))->setRadio(this->radio1);
	};
	
	~Engranaje(void){};

	void agrandar(){
		if (radio1 < RADIO_MAXENGRANAJE){
			this->radio1++;
			((Circulo*)(this->getDimension()))->setRadio(this->radio1);
			this->setCambio(true);
		}
	}

	void achicar(){
		if (radio1 > RADIO_MINENGRANAJE){
			this->radio1--;
			((Circulo*)(this->getDimension()))->setRadio(this->radio1);
			this->setCambio(true);
		}
	}

	virtual int getTipoDimension(){
		return ENGRANAJE;
	}

	void setRadio(double radio){
		this->radio1= radio;
		((Circulo*)(this->getDimension()))->setRadio(this->radio1);
		this->setCambio(true);
	}

	Figura* clonar(){
		Engranaje* eng = new Engranaje(ID.c_str(),dimension->clonar(),true);
		eng->setRadio(this->radio1);
		return eng;
	};
};
