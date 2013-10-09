#pragma once

#include <iostream>

class Posicion
{
protected:
	double x,y;
public:
	Posicion(){x=y=0;}
	Posicion(double x,double y){
		this->x=x;
		this->y=y;
	}
	virtual ~Posicion(){};
	double getX(){return x;}
	double getY(){return y;}
	virtual void setX(double x){
		this->x = x;
//		std::cout<<" X en posicion.h"<< x <<std::endl;
	}

	virtual void setY(double y){
		this->y = y;
//		std::cout<<" Y en posicion.h"<< y <<std::endl;
	}
};
