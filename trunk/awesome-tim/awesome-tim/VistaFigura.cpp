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
	
	int calcX = int(unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getX()) - img->getAncho()/2.0);
	int calcY = int(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getY()) - img->getAlto()/2.0);

	canvas->dibujarImagen(img,NULL,calcX,calcY);
}

void VistaFigura::redraw(EscalasDeEjes* unidadesLogicas){
	
	delete img;

	
	Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->ID.c_str()));
	
	//descomentar esto para que funcione como antes (acordarse de cambiar tambien figura.cpp esMiPosicion)
	//img = temp->rotarZoom(int(unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getAncho())),int(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getAlto())),fig->dimension->getAngulo());
	
	//cometnar esto para que ande como antes
	bool deleteTemp = false;
	Imagen* temp2 = temp->scaleImagen(int(unidadesLogicas->getCantidadUnidadesFisicasX(fig->dimension->getAncho())),int(unidadesLogicas->getCantidadUnidadesFisicasY(fig->dimension->getAlto())));
	img = temp2->rotarImagen(fig->dimension->getAngulo());
	delete temp2;
	//terminar de comentar aca

	if(fig->traslucido) img->setTransparency(180);

}