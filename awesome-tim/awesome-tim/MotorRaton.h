#pragma once
#include "Engranaje.h"
#include "Sonidos.h"
#include "Constantes.h"
#include "Circulo.h"
#include "VistaFiguraEstatica.h"
#include "SensorMRaton.h"
#include "Box2D/Box2D.h"

class MotorRaton : public Engranaje {

private:
	VistaFiguraEstatica* myVista2;
	MotorRaton(const char* id,Dimension* dim,bool flag):Engranaje(id,dim,flag){
		ID = ID_MOTOR_RATON_1;
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON);
		activo = false;
		contador = -1;
		distancia = DISTANCIA_RATON_DEFAULT;
		figAux = new SensorMRaton(this);
	};
	
	SensorMRaton* figAux;//la uso para meterle user data al contactListener en el box2d
	
public:
	int sentido;
	int contador;
	bool activo;
	double distancia;
	b2Body* B2Motor; //referencia al motor en el box 2d
public:
	MotorRaton(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Engranaje(ID_MOTOR_RATON,pos_X,pos_Y,radio1){
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR_RATON);
		activo = false;
		distancia = DISTANCIA_RATON_DEFAULT;
		figAux = new SensorMRaton(this);
	}

	~MotorRaton(void){
		delete figAux;
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
		if (this->distancia < DISTANCIA_RATON_DEFAULT){
			this->distancia = DISTANCIA_RATON_DEFAULT;
		}
		eng->setDistancia(this->distancia);
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

	virtual SensorMRaton* getFigAux(){return figAux;};

	virtual bool cortaSoga(){return false;}
	virtual bool pinchaGlobo(Dimension* dim){return false;}

	void ActivarMotor(){
		this->activo = true;
	}

	void DesactivarMotor(){
		this->activo = false;
	}


	void actualizarImagenDerecha(){
		int factor = 30;

		if(contador == 1){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA0);
		}
		
		if(contador == (FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA1);
		}

		if(contador == (2*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA2);
		}

		if(contador == (3*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA3);
		}

		if(contador == (4*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA2);
		}
		
		if(contador == (5*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA1);
		}
		
		if(contador == (6*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA0);
		}
		
		if(contador == (7*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA4);
		}
		
		if(contador == (8*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA5);
		}
		
		if(contador == (9*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA6);
		}
		
		if(contador == (10*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA5);
		}
		
		if(contador == (11*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_DERECHA4);
			contador = -1;
		}
		
	}

	void actualizarImagenIzquierda(){
		int factor = 30;

		if(contador == 1){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA0);
		}
		
		if(contador == (FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA1);
		}

		if(contador == (2*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA2);
		}

		if(contador == (3*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA3);
		}

		if(contador == (4*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA2);
		}
		
		if(contador == (5*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA1);
		}
		
		if(contador == (6*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA0);
		}
		
		if(contador == (7*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA4);
		}
		
		if(contador == (8*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA5);
		}
		
		if(contador == (9*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA6);
		}
		
		if(contador == (10*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA5);
		}
		
		if(contador == (11*FPS/factor)){
			delete(myVista2);
			myVista2 = new VistaFiguraEstatica(this,ID_RATON_MOVIENDOSE_IZQUIERDA4);
			contador = -1;
		}
		
	}

	void actualizar(){

		if(!motorActivo())
			return;

		//Sonidos::playSound(MOTOR_RATON_MUSIC);
		contador++;

		if(this->sentido == 1)
			actualizarImagenDerecha();
		else
			actualizarImagenIzquierda();

	}

	virtual bool tienePartesRotables(){return this->activo;};
	virtual double getAnguloPartesRotables(){
		return this->sentido;
	};
	virtual void setAnguloPartesRotables(double angulo){
		double sentido = angulo;
		contador++;
			if(this->sentido == 1)
				actualizarImagenDerecha();
			else
				actualizarImagenIzquierda();
	};
};
