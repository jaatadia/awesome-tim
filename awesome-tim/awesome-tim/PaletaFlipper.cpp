#include "PaletaFlipper.h"

PaletaFlipper::PaletaFlipper(void){

	this->interactua_en_play = true;

}

PaletaFlipper::~PaletaFlipper(void){
}

void PaletaFlipper::interactuar(int accion){

	//#define ANGULO_BALANCIN_IZQ 45
	//#define ANGULO_BALANCIN_DER 315

	if (accion == PRESS_SPACE){
		if (this->getDimension()->getAngulo() == ANGULO_BALANCIN_DER) this->setAngulo(ANGULO_BALANCIN_IZQ);
		else  this->setAngulo(ANGULO_BALANCIN_DER);
	}
};