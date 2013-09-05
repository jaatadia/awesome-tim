#include "VistaFigura.h"
#include "Contenedor.h"

VistaFigura::VistaFigura(Figura* fig){
	this->fig = fig;
	this->img = NULL;
}

VistaFigura::~VistaFigura(void){
}

void VistaFigura::dibujar(Superficie *canvas){
	if (this->fig->huboCambios()){
		redraw();			
	}
	this->fig->setCambio(false);

	int calcX = int(fig->pos.getX()- img->getAncho()/2.0);
	int calcY = int(fig->pos.getY()- img->getAlto()/2.0);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::dibujar(Superficie *canvas,double unidadesLogicas){
	if (this->fig->huboCambios()){
		redraw();			
	}
	this->fig->setCambio(false);

	int calcX = int(fig->pos.getX()* canvas->getAncho()/unidadesLogicas - img->getAncho()/2.0);
	int calcY = int(fig->pos.getY()* canvas->getAlto()/unidadesLogicas - img->getAlto()/2.0);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::redraw(){
	delete img;
	Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->ID));
	Imagen* temp2 = temp;
	
	if(fig->angulo!=0) temp2 = temp->rotarCuadradoImagen(fig->angulo);
	if((fig->dimension->getAncho()!=temp->getAncho())||(fig->dimension->getAlto()!= temp->getAlto())){
		Imagen* temp3 = temp2->scaleImagen(int(fig->dimension->getAncho()),int(fig->dimension->getAlto()));
		delete temp2;
		temp2 = temp3;
	}
	img = temp2;
}