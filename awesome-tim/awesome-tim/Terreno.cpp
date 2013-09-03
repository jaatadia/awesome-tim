#include "Terreno.h"

Terreno::Terreno(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);

}

Terreno::~Terreno(void){
	delete sup;
}

Superficie* Terreno::getImpresion(){
	return sup;
}