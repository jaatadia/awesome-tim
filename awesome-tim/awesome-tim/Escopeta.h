#pragma once

#include "Figura.h"
#include "Cuadrado.h"
#include "Bala.h"
#include "Sonidos.h"
#include "Box2D/Box2D.h"

class Escopeta: public Figura
{
public:
	b2Body* cuerpo;
	bool disparada;
private:
	bool atado;
	Escopeta(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		atado = false;
		disparada = false;
	}

public:
	Escopeta(double posX,double posY ,double angulo = 0):Figura(ID_ESCOPETA,new Cuadrado(ANCHO_ESCOPETA,ALTO_ESCOPETA,posX,posY,angulo)){
		atado = false;
		disparada = false;
	}
	
	~Escopeta(void){
	}

	virtual int getTipoFigura(){
		return ESCOPETA;
	}

	virtual int getTipoDimension(){
		return CUADRADO;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		return false;
	}

	virtual Figura* clonar(){
		return new Escopeta(ID.c_str(),dimension->clonar(),true);
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
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
		
		*x = cx + (-dimension->getAncho()*1/8)*coseno;
		*y = cy + (-dimension->getAncho()*1/8)*seno;
	}
	
	virtual void atarSoga(int numero){
		atado = true;
	}

	virtual void desatarSoga(int numero){
		atado = false;
	}

	Bala* disparar(){
		if (disparada) return NULL;

		disparada = true;
		Sonidos::playSound(FIRE_GUN);
		
		double cx = dimension->getX();
		double cy = dimension->getY();
		double coseno = cos(-dimension->getAngulo()*PI/180);
		double seno = sin(-dimension->getAngulo()*PI/180);

		double x = cx + (dimension->getAncho()/2+ANCHO_BALA/2)*coseno - (-dimension->getAlto()/2+1)*seno;
		double y = cy + (dimension->getAncho()/2+ANCHO_BALA/2)*seno + (-dimension->getAlto()/2+1)*coseno;

		return new Bala(x,y,dimension->getAngulo(),FUERZA_BALA*coseno,FUERZA_BALA*seno);
	}

};
