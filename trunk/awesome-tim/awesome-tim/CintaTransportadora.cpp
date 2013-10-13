#include "CintaTransportadora.h"
#include "VistaFigAgrandable.h"	

CintaTransportadora::CintaTransportadora(double largo,double posX,double posY,double angulo):Figura(ID_PLATAFORMA,new Cuadrado(ANCHO_PLATAFORMA*largo,ALTO_PLATAFORMA,posX,posY,angulo),false){
	this->largo = largo;
	this->myVista = new VistaFigAgrandable(this);
}

CintaTransportadora::~CintaTransportadora(void){
}

void CintaTransportadora::agrandar(){
	if (this->largo < PLATAFORMA_MAXLARGO){
		this->largo++;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}
}
void CintaTransportadora::achicar(){
	if (this->largo > 1){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}
}
double CintaTransportadora::getLargo(){
	return this->largo;
}
Figura* CintaTransportadora::clonar(){
	return new CintaTransportadora(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
}

void CintaTransportadora::setAngulo(double angulo){
		double margen = 2;
	if(
		(this->angulo < (angulo-margen))||
		(this->angulo>(angulo+margen))
	){
		this->angulo = angulo;
		setCambio(true);
	}
};
