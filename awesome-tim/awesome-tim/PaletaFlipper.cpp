#include "PaletaFlipper.h"

PaletaFlipper::PaletaFlipper(double posX,double posY,double angulo,int sentido):Figura(ID_PALETA,new Cuadrado(ANCHO_PALETA,ALTO_PALETA,posX,posY,angulo),true){

	this->interactua_en_play = true;
	this->push = false;
	this->sentido = sentido;

}

PaletaFlipper::~PaletaFlipper(void){
}

Figura* PaletaFlipper::clonar(){
	return new PaletaFlipper(this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo(),this->sentido);
}

int PaletaFlipper::getTipoFigura(){
	return PALETA;
}

int PaletaFlipper::getTipoDimension(){
	return CUADRADO;
}

double PaletaFlipper::getXdeRotacion(){
	return 0;
	}

double PaletaFlipper::getYdeRotacion(){
	return 0;
	}

void PaletaFlipper::interactuar(int accion){

	//#define ANGULO_BALANCIN_IZQ 45
	//#define ANGULO_BALANCIN_DER 315

	if (accion == PRESS_SPACE){
		this->push = true;
	}
};