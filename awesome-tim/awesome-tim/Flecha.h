#pragma once

#include "Figura.h"
#include "Cuadrado.h"

class Flecha: public Figura
{
public:
	double fuerzaX,fuerzaY;
private:
	bool atado;
	Flecha(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		fuerzaX = fuerzaY = 0;
	}

public:
	Flecha(double posX,double posY ,double angulo,double fuerzaX,double fuerzaY):Figura(ID_FLECHA,new Cuadrado(ANCHO_FLECHA,ALTO_FLECHA,posX,posY,angulo)){
		this->fuerzaX = fuerzaX;
		this->fuerzaY = fuerzaY;
	}
	
	~Flecha(void){
	}

	virtual int getTipoFigura(){
		return FLECHA;
	}

	virtual int getTipoDimension(){
		return CUADRADO;
	}

	virtual Figura* clonar(){
		Flecha* flecha = new Flecha(ID.c_str(),dimension->clonar(),true);
		flecha->fuerzaX = fuerzaX;
		flecha->fuerzaY = fuerzaY;
		return flecha;
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}

	virtual void getPunta(double* x,double* y){
		//busco el centro mio
		double cx = dimension->getX();
		double cy = dimension->getY();

		//busco el punto que pincha
		double px = cx + dimension->getAncho()/2-2;
		double py = cy ;
		
		//busco donde esta el punto que pincha segun mi angulo
		double coseno = cos( -dimension->getAngulo() * PI / 180);
		double seno = sin( -dimension->getAngulo() * PI / 180);

		*x = cx + (px - cx) * coseno - (py - cy) * seno;
		*y = cy + (px - cx) * seno + (py - cy) * coseno;
	}

	virtual bool pinchaGlobo(Dimension* dim){
		
		//busco el centro mio
		double cx = dimension->getX();
		double cy = dimension->getY();

		//busco el punto que pincha
		double px = cx + dimension->getAncho()/2 + 1;
		double py = cy ;
		
		//busco donde esta el punto que pincha segun mi angulo
		double coseno = cos( -dimension->getAngulo() * PI / 180);
		double seno = sin( -dimension->getAngulo() * PI / 180);

		double puntaRealX = cx + (px - cx) * coseno - (py - cy) * seno;
		double puntaRealY = cy + (px - cx) * seno + (py - cy) * coseno;

		return dim->puntoPertenece(puntaRealX,puntaRealY);
	}
};
