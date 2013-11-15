#include "VistaFigura.h"

VistaFigura::VistaFigura(Figura* fig){
	this->fig = fig;
	this->orig = NULL;
	this->rotada = NULL;
	this->modoGreedy = true;
	this->escalaAnterior = 0;
}

VistaFigura::~VistaFigura(void){
	delete orig;
	delete rotada;
}

void VistaFigura::dibujarEnPixel(Superficie *canvas){
	if (this->fig->huboCambios()||(orig==NULL)){
		redraw();			
		this->fig->setCambio(false);
	}
	
	int calcX = int(fig->dimension->getX()- rotada->getAncho()/2.0);
	int calcY = int(fig->dimension->getY()- rotada->getAlto()/2.0);

	canvas->dibujarImagen(rotada,NULL,calcX,calcY);
}

void VistaFigura::dibujar(Superficie *canvas){
	if (this==NULL) return;
	if (canvas==NULL) return;
	if (this->fig==NULL) return;

	if (this->fig->huboCambios()||(orig==NULL)||(rotada==NULL)){
		redraw();
		this->fig->setCambio(false);
	}
	
	int calcX = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->getDimension()->getX()) - rotada->getAncho()/2.0);
	int calcY = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->getDimension()->getY()) - rotada->getAlto()/2.0);

	canvas->dibujarImagen(rotada,NULL,calcX,calcY);
}

void VistaFigura::dibujar(Superficie *canvas,int xIni,int yIni){
	if (this->fig->huboCambios()||(orig==NULL)){
		redraw();			
		this->fig->setCambio(false);
	}
	
	int calcX = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->dimension->getX()) - rotada->getAncho()/2.0);
	int calcY = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->dimension->getY()) - rotada->getAlto()/2.0);

	canvas->dibujarImagen(rotada,NULL,calcX,calcY);
}

void VistaFigura::redraw(){
	
	if(modoGreedy==false){
		delete orig;
		Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->ID.c_str()));
		//descomentar esto para que funcione como antes (acordarse de cambiar tambien figura.cpp esMiPosicion)
		orig = temp->rotarZoom(int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->dimension->getAncho())),int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->dimension->getAlto())),fig->dimension->getAngulo());
		
		//cometnar esto para que ande como antes
		/*
		bool deleteTemp = false;
		Imagen* temp2 = temp->scaleImagen(int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->dimension->getAncho())),int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->dimension->getAlto())));
		img = temp2->rotarImagen(fig->dimension->getAngulo());
		delete temp2;
		//terminar de comentar aca
		*/
	}else{
		int tempAncho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->dimension->getAncho());
		if(orig==NULL || tempAncho!= escalaAnterior){
			delete orig;
			Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->ID.c_str()));
			orig = temp->scaleImagen(tempAncho,int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->dimension->getAlto())));
			escalaAnterior = tempAncho;
		}
		delete rotada;
		rotada = orig->rotarImagen(fig->dimension->getAngulo());
	}
	if(fig->traslucido) rotada->setTransparency(150);
	if(fig->superpuesta) rotada->pintarRojo();
}