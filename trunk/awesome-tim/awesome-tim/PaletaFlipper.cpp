#include "PaletaFlipper.h"

PaletaFlipper::PaletaFlipper(double posX,double posY,int sentido):Figura(ID_PALETA,new Cuadrado(ANCHO_PALETA,ALTO_PALETA,posX,posY,0),true){

	this->interactua_en_play = true;
	this->push = false;
	this->sentido = sentido;

	if (sentido == IZQUIERDA) this->setAngulo(PALETA_IZQ_MINANG);
	if (sentido == DERECHA) this->setAngulo(PALETA_DER_MINANG);

}

PaletaFlipper::~PaletaFlipper(void){
}

Figura* PaletaFlipper::clonar(){
	return new PaletaFlipper(this->dimension->getX(),this->dimension->getY(),this->sentido);
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

void PaletaFlipper::shift(){
	//this->sentido = (this->sentido+1) % 2; //porque IZQUIERDA Y DERECHA SON 0 Y 1 //ya no, lo cambie (?)
	if (this->sentido == IZQUIERDA) this->sentido = DERECHA;
	else this->sentido = IZQUIERDA;
}

void PaletaFlipper::interactuar(int accion){

	//#define ANGULO_BALANCIN_IZQ 45
	//#define ANGULO_BALANCIN_DER 315

	if (accion == PRESS_SPACE){
		this->push = true;
		//Sound
	}
};