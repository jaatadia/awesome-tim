#pragma once

#include "Figura.h"

class Chinche: public Figura
{
private:
	Chinche(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){}

public:
	Chinche(double posX,double posY ,double angulo = 0):Figura(ID_CHINCHE,new Cuadrado(BASE_CHINCHE,ALTURA_CHINCHE,posX,posY,angulo)){
	}
	
	~Chinche(void){
	}

	virtual int getTipoFigura(){
		return CHINCHE;
	}

	virtual int getTipoDimension(){
		return TRIANGULO;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		
		//busco el centro mio
		double cx = dimension->getX();
		double cy = dimension->getY();

		//busco el punto que pincha
		double px = cx + 0;
		double py = cy + dimension->getAlto()/2 + 0.1;
		
		//busco donde esta el punto que pincha segun mi angulo
		double coseno = cos( -dimension->getAngulo() * PI / 180);
		double seno = sin( -dimension->getAngulo() * PI / 180);

		double puntaRealX = cx + (px - cx) * coseno - (py - cy) * seno;
		double puntaRealY = cy + (px - cx) * seno + (py - cy) * coseno;

		return dim->puntoPertenece(puntaRealX,puntaRealY);
	}

	virtual Figura* clonar(){
		return new Chinche(ID.c_str(),dimension->clonar(),true);
	}

	virtual void shift(){
		this->setAngulo(dimension->getAngulo()+90);
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}

	virtual bool rotable(){return true;}
};
