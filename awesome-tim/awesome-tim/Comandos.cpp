#include "Comandos.h"

Comandos::Comandos(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
}

Comandos::~Comandos(void){
	delete sup;
}

Superficie* Comandos::getImpresion(){
	return sup;
}

Superficie* Comandos::getImpresion(EscalasDeEjes* escalas){
	return sup;
}
