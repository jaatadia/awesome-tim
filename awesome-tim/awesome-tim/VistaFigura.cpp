#include "VistaFigura.h"

VistaFigura::VistaFigura(Figura* fig){
	this->fig = fig;
}

VistaFigura::~VistaFigura(void){
}

void VistaFigura::dibujar(Superficie *canvas){
	if (this->fig->huboCambios()){
		redraw();			
	}
	this->fig->setCambio(false);
	canvas->dibujarImagen(img,NULL,int(fig->pos.getX()),int(fig->pos.getY()));
}

void VistaFigura::dibujar(Superficie *canvas,double unidadesLogicas){
	if (this->fig->huboCambios()){
		redraw();			
	}
	this->fig->setCambio(false);

	int calcX = int(fig->pos.getX()* canvas->getAncho()/unidadesLogicas);
	int calcY = int(fig->pos.getY()* canvas->getAlto()/unidadesLogicas);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::redraw(){

}