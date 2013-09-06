#include "Figura.h"

Figura::Figura(const char* ID,Dimension* dim){
	this->ID = ID;
	this->dimension = dim;
	this->setCambio(true);
	this->myVista = new VistaFigura(this);
}

Figura::~Figura(void){
	delete myVista;
	delete dimension;
}

void Figura::cambiarPosicion(double x,double y)
{
	dimension->setX( dimension->getX() + x);
	dimension->setY( dimension->getY() + y);
}

bool Figura::esMiPosicion(double x,double y)
{
	return dimension->puntoPertenece( x, y);
}

void Figura::dibujar(Superficie* super){
	myVista->dibujar(super);
}

void Figura::dibujar(Superficie* super,EscalasDeEjes* escalas){
	myVista->dibujar(super,escalas);
}
