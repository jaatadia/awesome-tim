#pragma once

#include "figura.h"
#include "Constantes.h"
#include "Circulo.h"

class Engranaje : public Figura
{
protected:
	Engranaje(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		atado = false;
	};
	double radio1;
	bool atado;

	Engranaje(const char* ID, double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Figura(ID,new Circulo(radio1,pos_X,pos_Y,angulo)){
		if (radio1< RADIO_MINENGRANAJE)	this->radio1 = RADIO_MINENGRANAJE;
		else if (radio1 > RADIO_MAXENGRANAJE) this->radio1 = RADIO_MAXENGRANAJE;
		else this->radio1 = int(radio1);
		atado = false;

		((Circulo*)(this->getDimension()))->setRadio(this->radio1);
	};

public:

	Engranaje(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Figura(ID_ENGRANAJE,new Circulo(radio1,pos_X,pos_Y,angulo)){
		if (radio1< RADIO_MINENGRANAJE)	this->radio1 = RADIO_MINENGRANAJE;
		else if (radio1 > RADIO_MAXENGRANAJE) this->radio1 = RADIO_MAXENGRANAJE;
		else this->radio1 = int(radio1);
		atado = false;

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

	virtual void setRadio(double radio){
		this->radio1= int(radio);
		((Circulo*)(this->getDimension()))->setRadio(this->radio1);
		this->setCambio(true);
	}

	virtual double getRadio(){
		return this->radio1;
	}

	Figura* clonar(){
		Engranaje* eng = new Engranaje(ID.c_str(),dimension->clonar(),true);
		eng->setRadio(this->radio1);
		return eng;
	};

	virtual int getTipoFigura(){return ENGRANAJE;}
	virtual int getTipoDimension(){return CIRCULO;}
	virtual bool esAtableCorrea(){return !atado;}
	virtual void atarCorrea(){atado = true;}
	virtual void desatarCorrea(){atado = false;}

	bool choqueConFigura(Figura* fig){

		//me fijo si fig que me pasaron choca con esta dimension (para cada una que tenga en este caso solo 1)
		bool choca = false;

		Dimension* dimAux = new Circulo(PORCENTAJE_SUPERPOSICION_ENGRANAJE * getRadio() ,dimension->getX(),dimension->getY(),dimension->getAngulo());

		Dimension* dimensionRotada = dimAux->rotarDimension(dimension->getX(),dimension->getY(),dimension->getAngulo());

		choca = fig->choqueConDimension(dimensionRotada);
		//caso en que una esta dentro de la otra
		if ( (!choca) && fig->esMiPosicion(this->getDimension()->getX() , this->getDimension()->getY()) ){
			choca = true;
		}

		delete dimensionRotada;
		delete dimAux;

		return choca;
	}


	bool choqueConDimension(Dimension* dim){

		Dimension* dimAux = new Circulo(getRadio() ,dimension->getX(),dimension->getY(),dimension->getAngulo());
		
		bool choca = dimAux->choqueConDimension(dim);

		delete dimAux; 

		return choca;
	}

	virtual bool cortaSoga(){
		return dimension->getAngulo()!=0;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		return dimension->getAngulo()!=0;
	}
};
