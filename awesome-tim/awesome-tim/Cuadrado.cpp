#include "Cuadrado.h"

Cuadrado::Cuadrado(double ancho,double alto,double X, double Y, double angulo): Dimension(X,Y,angulo) {
	this->ancho = ancho;
	this->alto = alto;
}

Cuadrado::~Cuadrado(void){
}

double Cuadrado::getAncho(){
	return ancho;
}

double Cuadrado::getAlto(){
	return alto;
}

bool Cuadrado::puntoPertenece(double X, double Y){

	double bordeLeft,bordeRight,bordeUp,bordeDown;

	bordeLeft = getX() - getAncho()/2 ;
	bordeRight = getX() + getAncho()/2;
	bordeUp = getY() + getAlto()/2;
	bordeDown = getY() - getAlto()/2;

	if  ((X>=bordeLeft) && (X<=bordeRight) && (Y>=bordeDown) && (Y<=bordeUp))
		return true;

	return false;

}