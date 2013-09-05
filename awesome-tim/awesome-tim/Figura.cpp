#include "Figura.h"

Figura::Figura(char* dir,int angulo,double posX,double posY){
	this->dirImagen = dir;
	this->angulo = angulo;
	this->pos = Posicion(posX,posY);
	this->setCambio(true);
	this->myVista = new VistaFigura(this);
};
Figura::~Figura(void){
	delete myVista;
};

