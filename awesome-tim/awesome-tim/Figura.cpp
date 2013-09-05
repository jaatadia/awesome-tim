#include "Figura.h"

Figura::Figura(const char* ID,Dimension* dim,int angulo,double posX,double posY){
	this->ID = ID;
	this->dimension = dim;
	this->angulo = angulo;
	this->pos = Posicion(posX,posY);
	this->setCambio(true);
	this->myVista = new VistaFigura(this);
};
Figura::~Figura(void){
	delete myVista;
	delete dimension;
};

void Figura::dibujar(Superficie* super){
	myVista->dibujar(super);
};
