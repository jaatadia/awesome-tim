#include "Plataforma.h"

Plataforma::Plataforma(double largo,double posX,double posY,double angulo):Figura(ID_PLATAFORMA,new Cuadrado(ANCHO_PLATAFORMA*largo,ALTO_PLATAFORMA,posX,posY,angulo),false){
	this->largo = largo;
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
	if (this->largo > PLATAFORMA_MINLARGO){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}
}
double Plataforma::getLargo(){
	return this->largo;
}
Figura* Plataforma::clonar(){
	return new Plataforma(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
}
int Plataforma::getTipoFigura(){
	return PLATAFORMA;
}
int Plataforma::getTipoDimension(){
	return CUADRADO;
}