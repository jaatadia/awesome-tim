#include "Terreno.h"
#include "ErrorLogHandler.h"
#include <new>

Terreno::Terreno(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);
	this->figuras = std::list<Figura*>();
	figuraActiva=NULL;
	img=NULL;
	fondoID=""; //sin fondo seria asi? (con NULL se rompe)
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

void Terreno::redraw(EscalasDeEjes* escalas){
	//recorro todas las figuras y las voy dibujando

	if(this->img == NULL) sup->restore();//antes repinto todo de negro asi no quedan rastros de movimiento
	else sup->dibujarImagen(this->img,NULL,0,0);
	

	
	std::list<Figura*>::iterator iteradorLista;

	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		(*iteradorLista)->dibujar(this->sup, escalas);
	}
	//por ultimo dibujo la que estoy manipulando;
	if (figuraActiva)
		figuraActiva->dibujar(this->sup,escalas);
}

Superficie* Terreno::getImpresion(EscalasDeEjes* escalas){
	if(this->huboCambios()) redraw(escalas);
	this->setCambio(false);
	return sup;
}

void Terreno::redraw(){}

Superficie* Terreno::getImpresion(){
	if(this->huboCambios()) redraw();
	this->setCambio(false);
	return sup;
}

void Terreno::setFondo(const char* ruta_img){
	Imagen* temp = new Imagen(ruta_img);
	if(!temp->huboFallos()){
		this->setCambio(true);
		delete this->img;
		this->img = temp->scaleImagen(this->ancho,this->alto);
		fondoID = ruta_img;
	}
	delete temp;
}

void Terreno::agregarFigura(Figura* fig){

	try{
	(this->figuras).push_back(fig);
	} catch (...) {
		ErrorLogHandler::addError("agregarFigura","excepcion al agregar en la lista (figuras.push_back)");
		//si hay error, tira la excepcion nomas? y termina no haciendo nada???
	};
}

void Terreno::rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY){
	//practicamente lo mismo que arrastraFigura
	if (hayFiguras()){
		if (figuraActiva == NULL){
			Figura* figuraAMover = NULL;

			bool figuraEncontrada = false;

			std::list<Figura*>::reverse_iterator iteradorLista;
			iteradorLista = figuras.rbegin();

			while (iteradorLista != figuras.rend() && !figuraEncontrada ) {
				
				figuraEncontrada = (*iteradorLista)->esMiPosicion(posClickX,posClickY);
				figuraAMover = (*iteradorLista);
				
				iteradorLista++;
			}

			if (figuraEncontrada){
				eliminarFigura(figuraAMover);
				figuraActiva=figuraAMover;

				double X2,Y2;
				X2 = posClickX + cantMovX;
				Y2 = posClickY + cantMovY;

				figuraActiva->cambiarAngulo(posClickX,posClickY,X2,Y2);
				setCambio(true);
			}
		}else{
			//calculo el angulo y se lo pongo a figura
			double X2,Y2;
			X2 = posClickX + cantMovX;
			Y2 = posClickY + cantMovY;

			figuraActiva->cambiarAngulo(posClickX,posClickY,X2,Y2);
			setCambio(true);
		}
	}
}


void Terreno::eliminarFigura(Figura* fig){

	try{
	(this->figuras).remove(fig);
	} catch (...) {
		ErrorLogHandler::addError("eliminarFigura","excepcion al eliminar una figura de la lista (figuras.remove)");
	};
}

void Terreno::arrastrarFigura(double posClickX,double posClickY,double cantMovX,double cantMovY)
{
	//recorro lista de figuras hasta saber si hay alguna en esta posicion
	//a la primera que encuentro la saco de la lista le cambio la pos
	//y la vuelvo a meter en ultimo lugar cuando se suelta el boton (ver onEvent de juego)
	//para que si se superpone quede arriba al dibujarse
	if(hayFiguras()){	
		if (figuraActiva == NULL){
			Figura* figuraAMover = NULL;

			bool figuraEncontrada = false;
			//recorro al reves asi "agarro" la figura dibujada arriba
			std::list<Figura*>::reverse_iterator iteradorLista;
			iteradorLista = figuras.rbegin();

			while (iteradorLista != figuras.rend() && !figuraEncontrada ) {
				
				figuraEncontrada = (*iteradorLista)->esMiPosicion(posClickX,posClickY);
				figuraAMover = (*iteradorLista);
				
				iteradorLista++;
			}

			if (figuraEncontrada){
				eliminarFigura(figuraAMover);
				figuraActiva=figuraAMover;
				figuraActiva->cambiarPosicion(cantMovX, cantMovY);
				setCambio(true);
			}
		}else{
			figuraActiva->cambiarPosicion(cantMovX, cantMovY);
			setCambio(true);
		}

	}
}

void Terreno::soltarFigura()
{
	if (figuraActiva){
		agregarFigura(figuraActiva);
		figuraActiva=NULL;
	}
}

bool Terreno::hayFiguras(){

	if ((figuraActiva != NULL)||(!figuras.empty()))
		return true;

	return false;
}

void Terreno::borrarFigura(double posClickX, double posClickY){
//aca ya no puede haber una figura activa, porque solo se llega al hacer un shift-click
	if(hayFiguras()){	
		Figura* figuraABorrar = NULL;

		bool figuraEncontrada = false;
		//recorro al reves asi "agarro" la figura dibujada arriba
		std::list<Figura*>::reverse_iterator iteradorLista;
		iteradorLista = figuras.rbegin();

		while (iteradorLista != figuras.rend() && !figuraEncontrada ) {
			
			figuraEncontrada = (*iteradorLista)->esMiPosicion(posClickX,posClickY);
			figuraABorrar = (*iteradorLista);
			
			iteradorLista++;
		}

		if (figuraEncontrada){
			//saco de la lista y libero memoria
			eliminarFigura(figuraABorrar);
			setCambio(true);
			delete figuraABorrar;
		}
	}
}

int Terreno::getAncho(){
	return (this->ancho);
};
int Terreno::getAlto(){
	return (this->alto);
};
const char* Terreno::getFondo(){ //si es "" es porq no pusieron ningun fondo (esta el default)
	return this->fondoID;
};
std::list<Figura*> Terreno::getListaFigs(){
	return this->figuras;
};