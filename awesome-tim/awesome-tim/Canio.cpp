#include "Canio.h"

Canio::Canio(int largo,double posX,double posY,double angulo):Figura(ID_CANIO,new Cuadrado(ANCHO_CANIO*largo,ALTO_CANIO,posX,posY,angulo),false){
	this->largo = largo;
	this->myVista = new VistaFigAgrandable(this);
}
Canio::~Canio(void){
}
void Canio::agrandar(){
	if (this->largo < CANIO_MAXLARGO){
		this->largo++;
		this->getDimension()->setAncho(ANCHO_CANIO*largo);
		setCambio(true);
	}
}
void Canio::achicar(){
	if (this->largo > CANIO_MINLARGO){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_CANIO*largo);
		setCambio(true);
	}
}
int Canio::getLargo(){
	return this->largo;
}
Figura* Canio::clonar(){
	return new Canio(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
}
int Canio::getTipoFigura(){
	return CANIO;
}
int Canio::getTipoDimension(){
	return CUADRADO;
}

void Canio::setLargo(int largoN){
	
	if (largoN <= PLATAFORMA_MAXLARGO && largoN >= CANIO_MINLARGO){
		largo = largoN;
		this->getDimension()->setAncho(ANCHO_CANIO*largo);
		setCambio(true);
	}

}