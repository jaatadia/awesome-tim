#include "Plataforma.h"

Plataforma::Plataforma(double largo,double posX,double posY,double angulo):Figura(ID_PLATAFORMA,new Cuadrado(ANCHO_PLATAFORMA*largo,ALTO_PLATAFORMA,posX,posY,angulo)){
	this->largo = largo;
	delete this->myVista;
	this->myVista = new VistaFigAgrandable(this);
}

Plataforma::~Plataforma(void){
}
void Plataforma::agrandar(){
	if (this->largo < PLATAFORMA_MAXLARGO){
		this->largo++;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}
}
void Plataforma::achicar(){
	if (this->largo > 1){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}
}
int Plataforma::getTipoDimension(){
	return PLATAFORMA;
}
double Plataforma::getLargo(){
	return this->largo;
}