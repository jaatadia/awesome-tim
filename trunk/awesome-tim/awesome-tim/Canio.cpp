#include "Canio.h"

Canio::Canio(int largo,double posX,double posY,double angulo):Figura(ID_CANIO,new Cuadrado(ANCHO_CANIO*largo,ALTO_CANIO,posX,posY,angulo),false){
	if(largo<=0){
		this->largo = 1;
		this->getDimension()->setAncho(ANCHO_CANIO*1);
	}else{
		this->largo = largo;
	}
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
	Figura* canio = new Canio(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
	this->completarInteraccionesPosibles(canio);
	return canio;
}
int Canio::getTipoFigura(){
	return CANIO;
}
int Canio::getTipoDimension(){
	return CUADRADO;
}

void Canio::setLargo(int largoN){
	
	if (largoN <= CANIO_MAXLARGO && largoN >= CANIO_MINLARGO){
		largo = largoN;
		this->getDimension()->setAncho(ANCHO_CANIO*largo);
		setCambio(true);
	}

}
void Canio::getPosPared1(double* x,double* y){
	double alto = this->getDimension()->getAlto();
	double Xc = this->getDimension()->getX();
	double coseno = cos(-this->getDimension()->getAngulo()*PI/180);
	double seno = sin(-this->getDimension()->getAngulo()*PI/180);
	double Yc  = this->getDimension()->getY();
	double Y = Yc-alto/2+CANIO_BORDE/2;
	*x = Xc - (Y-Yc)*seno;
	*y = Yc + (Y-Yc)*coseno;
}
void Canio::getPosPared2(double* x,double* y){
	double alto = this->getDimension()->getAlto();
	double Xc = this->getDimension()->getX();
	double coseno = cos(-this->getDimension()->getAngulo()*PI/180);
	double seno = sin(-this->getDimension()->getAngulo()*PI/180);
	double Yc  = this->getDimension()->getY();
	double Y = Yc+alto/2-CANIO_BORDE/2;
	*x = Xc - (Y-Yc)*seno;
	*y = Yc + (Y-Yc)*coseno;
}