#include "Contenedor.h"
#include "Imagen.h"
#include <iostream>

Contenedor* Contenedor::cont = NULL;

void Contenedor::putMultimedia(const char* ID,void* medio){
	if (cont == NULL){
		cont = new Contenedor();
		cont->mapa["NONE"] = new Imagen("NONE");
	}
	cont->mapa[ID]=medio;
}

void* Contenedor::getMultimedia(const char* ID){
	if (cont == NULL){
		cont = new Contenedor();
	}
	if(cont->mapa.find(ID)!= cont->mapa.end()) return cont->mapa[ID];
	else return cont->mapa["NONE"];
}

void Contenedor::deleteContenedor(){
	delete cont;
}


Contenedor::Contenedor(void){
}

Contenedor::~Contenedor(void){
}
