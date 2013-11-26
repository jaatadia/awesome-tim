#pragma once

#include "Figura.h"
#include "Cuadrado.h"
#include "Flecha.h"
#include "Sonidos.h"

class Arco: public Figura
{
private:
	bool atado;
	bool disparado;
	Arco(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		atado = false;
		disparado = false;
	}

public:
	Arco(double posX,double posY ,double angulo = 0):Figura(ID_ARCO,new Cuadrado(ANCHO_ARCO,ALTO_ARCO,posX,posY,angulo)){
		atado = false;
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
		Figura* arco = new Arco(ID.c_str(),dimension->clonar(),true);
		this->completarInteraccionesPosibles(arco);
		return arco;
	}

	virtual bool rotable(){return true;}

	
	virtual int esAtableSoga(double x,double y){
		if(!atado) return 1;
		return -1;
	}
	
	virtual void posAtableSoga(int numero,double* x,double* y){
	
		double cx = dimension->getX();
		double cy = dimension->getY();
		double coseno = cos(-dimension->getAngulo()*PI/180);
		double seno = sin(-dimension->getAngulo()*PI/180);
		
		if(!atado){
			*x = cx;
			*y = cy;
		}else{
			*x = cx + (-dimension->getAncho()/2+1)*coseno;
			*y = cy + (-dimension->getAncho()/2+1)*seno;
		}
	}
	
	virtual void atarSoga(int numero){
		atado = true;
	}

	virtual void desatarSoga(int numero){
		atado = false;
	}

	Flecha* disparar(){
		if((!atado)&&(!disparado)){
			disparado = true;
			delete myVista;
			this->ID = ID_ARCO2;
			
			//Sonidos::playSound(SHOT_ARROW);
			
			this->myVista = new VistaFigura(this);
			
			double cx = dimension->getX();
			double cy = dimension->getY();
			double coseno = cos(-dimension->getAngulo()*PI/180);
			double seno = sin(-dimension->getAngulo()*PI/180);

			double x = cx + (dimension->getAncho()/2+ANCHO_FLECHA/2)*coseno;
			double y = cy + (dimension->getAncho()/2+ANCHO_FLECHA/2)*seno;
			
			return new Flecha(x,y,dimension->getAngulo(),FUERZA_FLECHA*coseno,FUERZA_FLECHA*seno);
		}else{
			return NULL;
		}
	}

};

