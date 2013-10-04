#pragma once

class Posicion
{
private:
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
	void setX(double x){this->x = x;}
	void setY(double y){this->y = y;}
};
