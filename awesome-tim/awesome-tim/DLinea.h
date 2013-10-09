#pragma once

#include "Dimension.h"
#include "Constantes.h"

class DLinea: public Dimension
{
public:
	double x1, y1, x2, y2, ancho;
public:
	DLinea(double x1,double y1,double x2,double y2,double ancho):Dimension(x1,y1,0){
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->ancho = ancho;
	};

	~DLinea(void){};

	virtual double getAncho(){return 10;};
	virtual double getAlto(){return 10;};
	
	virtual int getTipoDimension(){return LINEA;};
	
	virtual Dimension* clonar(){return new DLinea(x1,y1,x2,y2,ancho);};

	bool puntoPertenece(double pos_X, double pos_Y){
		return false;
	};

	
	void putP1(double x,double y){
		this->x1 = x;
		this->y1 = y;
	}

	void putP2(double x,double y){
		setX(x);
		setY(y);
	}

	void setX(double x){
		this->x = x;
		this->x2 = x;
	};

	void setY(double y){
		this->y = y;
		this->y2 = y;
	};
};
