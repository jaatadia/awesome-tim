#include "Circulo.h"
#include <math.h>
#include "Constantes.h"
#include "PoligonoRegular.h"

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

double Circulo::getRadio(){
	return (this->radio);
}

void Circulo::setRadio(double radio){
	this->radio = radio;
}

bool Circulo::puntoPertenece(double X, double Y){

	double moduloCuadrado = (X-getX())*(X-getX())+ (Y-getY())*(Y-getY());
	double modulo= sqrt(moduloCuadrado);

	return modulo<=radio;
}


bool Circulo::intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2){

	//envuelvo en un poligono de 50 vertices
	PoligonoRegular polEnvolvente(this->getX(),this->getY(),this->getRadio(),50,this->getAngulo());

	bool interseca = polEnvolvente.intersecaCon(Xs1, Ys1, Xs2, Ys2);

	return interseca;
}

Dimension* Circulo::clonar(){
	return new Circulo(this->radio,this->getX(),this->getY(),this->getAngulo());
}

Dimension* Circulo::devolverPoligonEnvolvente(){

	return (new PoligonoRegular(this->getX(),this->getY(),this->getRadio(),50,this->getAngulo()));
}

bool Circulo::choqueConDimension(Dimension* dim){

	//envuelvo en un poligono de 50 vertices
	PoligonoRegular* polEnvolvente = (PoligonoRegular*)devolverPoligonEnvolvente();
	
	//y lo choco con el que me pasaron

	bool interseca = dim->choqueConDimension(polEnvolvente);

	delete polEnvolvente;

	return interseca;
}