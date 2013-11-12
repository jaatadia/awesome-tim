#include "Rectangulo.h"

//crea el rectangulo
Rectangulo::Rectangulo(){ 
	this->x = 0;
	this->y = 0;
	this->ancho = 0;
	this->alto = 0;
}

//crea el rectangulo
Rectangulo::Rectangulo(double x,double y,double ancho,double alto){ 
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
}

//destruye el rectangulo
Rectangulo::~Rectangulo(void){}

//devuelve true si el punto pasado es parte del rectangulo
bool Rectangulo::isIn(double x, double y){
	if((x>=this->x)&&(x<=(this->x+this->ancho))&&(y>=this->y)&&(y<=(this->y+this->alto)))return true;
	else return false;
}