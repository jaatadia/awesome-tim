#include "Comandos.h"

Comandos::Comandos(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	sup->restoreGris();
	sup->dibujarCuadradoNegro(ancho/16,alto/8,ancho*6/8,alto*6/8);
	this->setCambio(true);
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
