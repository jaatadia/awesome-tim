#include "Cuadrado.h"

Cuadrado::Cuadrado(double ancho,double alto){
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