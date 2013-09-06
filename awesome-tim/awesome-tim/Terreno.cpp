#include "Terreno.h"
#include "ErrorLogHandler.h"
#include <new>

Terreno::Terreno(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	this->figuras = std::list<Figura*>();
	img=NULL;
}

Terreno::~Terreno(void){

	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		delete (*iteradorLista);
	}
	if (img)
		delete img;

	delete sup;
}

Superficie* Terreno::getImpresion(EscalasDeEjes* escalas){
	//recorro todas las figuras y las voy dibujando

	sup->restore();//antes repinto todo de negro asi no quedan rastros de movimiento
	
	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->dibujar(this->sup, escalas);
	}

	return sup;
}

Superficie* Terreno::getImpresion(){
	return sup;
}

void Terreno::setFondo(const char* ruta_img){
	this->img = new Imagen(ruta_img);
}

void Terreno::agregarFigura(Figura* fig){

	try{
	(this->figuras).push_back(fig);
	} catch (std::exception& e) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
}

//void Terreno::rotarFigura(Figura* fig);

void Terreno::eliminarFigura(Figura* fig){

	try{
	(this->figuras).remove(fig);
	} catch (std::exception& e) {
		ErrorLogHandler::addError("eliminarFigura","excepcion al eliminar una figura de la lista (figuras.remove)");
	};
}

void Terreno::arrastrarFigura(double posClickX,double posClickY,double cantMovX,double cantMovY)
{
	//recorro lista de figuras hasta saber si hay alguna en esta posicion
	//a la primera que encuentro la saco de la lista le cambio la pos
	//y la vuelvo a meter en ultimo lugar para que si se superpone que arriba al dibujarse
	Figura* figuraAMover = NULL;

	std::list<Figura*>::iterator iteradorLista;
	iteradorLista = figuras.begin();

	bool figuraEncontrada = false;

	while (iteradorLista != figuras.end() && !figuraEncontrada ) {
		
		figuraEncontrada = (*iteradorLista)->esMiPosicion(posClickX,posClickY);
		figuraAMover = (*iteradorLista);
		
		iteradorLista++;
	}

	if (figuraEncontrada){
		figuras.erase(--iteradorLista);
		figuraAMover->cambiarPosicion(cantMovX, cantMovY);
		figuras.push_back(figuraAMover);
	}

	setCambio(true);
}