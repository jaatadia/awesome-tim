#include "VistaFigura.h"
#include "Contenedor.h"

VistaFigura::VistaFigura(Figura* fig){
	this->fig = fig;
	this->img = NULL;
}

VistaFigura::~VistaFigura(void){
}

void VistaFigura::dibujarEnPixel(Superficie *canvas,EscalasDeEjes* unidadesLogicas){
	if (this->fig->huboCambios()){
		redraw(unidadesLogicas);			
	}
	this->fig->setCambio(false);

	int calcX = int(fig->dimension->getX()- img->getAncho()/2.0);
	int calcY = int(fig->dimension->getY()- img->getAlto()/2.0);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::dibujar(Superficie *canvas,EscalasDeEjes* unidadesLogicas){
	if (this->fig->huboCambios()){
		redraw(unidadesLogicas);			
	}
	this->fig->setCambio(false);
	
	int calcX = int(unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getX()) - img->getAncho()/2.0);
	int calcY = int(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getY()) - img->getAlto()/2.0);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::redraw(EscalasDeEjes* unidadesLogicas){
	delete img;
	Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->ID));
	Imagen* temp2 = temp;
	
	if(fig->dimension->getAngulo()!=0) temp2 = temp->rotarCuadradoImagen(fig->dimension->getAngulo());
	if((unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getAncho())!= temp->getAncho())||
		(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getAlto())!= temp->getAlto())){
		Imagen* temp3 = temp2->scaleImagen(int(unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getAncho())),int(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getAlto())));
		delete temp2;//comentar para rotar figura... 
		temp2 = temp3;
	}
	img = temp2;
}