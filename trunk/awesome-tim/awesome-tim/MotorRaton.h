#pragma once
#include "Engranaje.h"
#include "Constantes.h"
#include "Circulo.h"
#include "VistaFiguraEstatica.h"

class MotorRaton : public Engranaje {

private:
	VistaFiguraEstatica* myVista2;
	MotorRaton(const char* id,Dimension* dim,bool flag):Engranaje(id,dim,flag){
		ID = ID_MOTOR_RATON_1;
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON);
		activo = false;
	};
	
public:
	int sentido;
	bool activo;
	double distancia;

public:
	MotorRaton(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Engranaje(ID_MOTOR_RATON,pos_X,pos_Y,radio1){
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON);
		activo = false;
		distancia = 0;
	}

	~MotorRaton(void){
		delete myVista2;
	};
	
	void setDistancia(double dist){
		this->distancia =dist;
	}

	virtual Figura* clonar(){
		MotorRaton* eng = new MotorRaton(ID_MOTOR_RATON_1,dimension->clonar(),true);
		eng->setRadio(this->radio1);
		if(this->sentido == -1) eng->shift();
		this->completarInteraccionesPosibles(eng);
		return eng;
	};

	virtual const char* getIDBotonera(){ return ID_RATON_COMPLETO;};

	virtual int getTipoFigura(){return MOTOR_RATON;}
	virtual int getTipoDimension(){return CUADRADO;}

	virtual void shift(){
		this->sentido = -this->sentido;
		delete this->myVista;
		if(sentido == 1){
			delete(myVista2);		
			myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON);
			this->ID = ID_MOTOR_RATON_1;
		}else
		if(sentido == -1){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON_OPUESTO);
			this->ID = ID_MOTOR_RATON_2;
		}
		this->myVista = new VistaFigura(this);
		this->setCambio(true);
	}
	
	void dibujar(Superficie* super){
		myVista2->dibujar(super);
		myVista->dibujar(super);
		setCambio(false);
	}

	bool motorActivo(){
		return activo;
	}

	bool choqueConFigura(Figura* fig){

		//me fijo si fig que me pasaron choca con esta dimension (para cada una que tenga en este caso solo 1)
		bool choca = false;

		Dimension* dimAux = new Cuadrado(dimension->getAncho(),dimension->getAncho(),dimension->getX(),dimension->getY(),dimension->getAngulo());

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

		Dimension* dimAux = new Cuadrado(dimension->getAncho(),dimension->getAncho(),dimension->getX(),dimension->getY(),dimension->getAngulo());
		
		bool choca = dimAux->choqueConDimension(dim);

		delete dimAux; 

		return choca;
	}

	virtual bool cortaSoga(){return false;}
	virtual bool pinchaGlobo(Dimension* dim){return false;}

	void ActivarMotor(){
		activo = true;
	}

	void DesactivarMotor(){
		activo = false;
	}
};
