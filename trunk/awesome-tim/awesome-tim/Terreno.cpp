#include "Terreno.h"
#include "ErrorLogHandler.h"
#include <new>

Terreno::Terreno(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	this->figuras = std::list<Figura*>();
}

Terreno::~Terreno(void){
	delete sup;
}

Superficie* Terreno::getImpresion(){
	return sup;
}

//void Terreno::setFondo(Imagen* img); ni idea que tiene q hacer esto

void Terreno::agregarFigura(Figura* fig){

	try{
	(this->figuras).push_back(fig);
	} catch (std::exception& e) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
};

//void Terreno::rotarFigura(Figura* fig);

void Terreno::eliminarFigura(Figura* fig){

	try{
	(this->figuras).remove(fig);
	} catch (std::exception& e) {
		ErrorLogHandler::addError("eliminarFigura","excepcion al eliminar una figura de la lista (figuras.remove)");
	};
};