#include "Circulo.h"
#include <math.h>
#include "Constantes.h"

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

bool Circulo::puntoPertenece(double X, double Y){

	double moduloCuadrado = (X-getX())*(X-getX())+ (Y-getY())*(Y-getY());
	double modulo= sqrt(moduloCuadrado);

	return modulo<=radio;
}

//probe en muchos puntos, ya que encerrarlo en un cuadrado fallaba y no se me ocurre otra manera
bool Circulo::intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2){

	double angle = -(PI*this->getAngulo())/180.0;
	Xs1 = getX() + ((Xs1-getX()) * cos(-angle)) - ((Ys1-getY()) * sin(-angle));
	Ys1 = getY() + ((Xs1-getX()) * sin(-angle)) + ((Ys1-getY()) * cos(-angle));
	Xs2 = getX() + ((Xs2-getX()) * cos(-angle)) - ((Ys2-getY()) * sin(-angle));
	Ys2 = getY() + ((Xs2-getX()) * sin(-angle)) + ((Ys2-getY()) * cos(-angle));

	Segmento* segExterno = new Segmento(Xs1, Ys1, Xs2, Ys2);

	bool interseca = false;	

	//intersecar con muchos puntos...
	for (double i = 0; i<radio ; i+= (radio * 0.01) ){
		interseca = puntoPertenece(i,segExterno->evaluar(i));

		if (interseca){
			break;
		}
	}

	return interseca;
}

Dimension* Circulo::clonar(){
	return new Circulo(radio,getX(),getY(),getAngulo());
}