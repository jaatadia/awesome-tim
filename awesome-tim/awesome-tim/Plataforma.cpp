#include "Plataforma.h"

Plataforma::Plataforma(int largo,double posX,double posY,double angulo):Figura(ID_PLATAFORMA,new Cuadrado(ANCHO_PLATAFORMA*largo,ALTO_PLATAFORMA,posX,posY,angulo),false){
	if(largo<=0){
		this->largo = 1;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*1);
	}else{
		this->largo = largo;
	}
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
int Plataforma::getLargo(){
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

void Plataforma::setLargo(int largoN){
	
	if (largoN <= PLATAFORMA_MAXLARGO && largoN >= PLATAFORMA_MINLARGO){
		largo = largoN;
		this->getDimension()->setAncho(ANCHO_PLATAFORMA*largo);
		setCambio(true);
	}

}

