#include "Botonera.h"

Botonera::Botonera(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
}

Botonera::~Botonera(void){
	delete sup;
}

Superficie* Botonera::getImpresion(){
	return sup;
}