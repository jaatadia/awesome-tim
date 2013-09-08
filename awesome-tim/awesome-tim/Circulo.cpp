#include "Circulo.h"
#include <math.h>

//da error esta mierda
Circulo::Circulo(double r,double pos_X,double pos_Y,double angulo): Dimension(pos_X,pos_Y,angulo){
	this->radio = r;
}

Circulo::~Circulo(void){
}

double Circulo::getAncho(){
	return (2*(this->radio));
}

double Circulo::getAlto(){
	return (2*(this->radio));
}

bool Circulo::puntoPertenece(double X, double Y){

	double moduloCuadrado = (X-getX())*(X-getX())+ (Y-getY())*(Y-getY());
	double modulo= sqrt(moduloCuadrado);

	return modulo<=radio;
}