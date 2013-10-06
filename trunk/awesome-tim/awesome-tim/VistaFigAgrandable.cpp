#include "VistaFigAgrandable.h"

VistaFigAgrandable::VistaFigAgrandable(Figura* fig){
	this->fig = fig;
	this->orig = NULL;
	this->rotada = NULL;
	this->escalaAnterior = 0;
}

VistaFigAgrandable::~VistaFigAgrandable(void){
}
void VistaFigAgrandable::dibujar(Superficie *canvas){
	
	//if (this->fig->huboCambios()){
	//	redraw();
	//	this->fig->setCambio(false);
	//}
	//
	//for (int i=0;i<fig->getLargo();i++){

	//	int calcX = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->dimension->getX()) - rotada->getAncho()/2.0);
	//	int calcY = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->dimension->getY()) - rotada->getAlto()/2.0);
	//
	//	canvas->dibujarImagen(rotada,NULL,calcX,calcY);
	//};

	
}
void VistaFigAgrandable::dibujarEnPixel(Superficie *canvas){
	dibujar(canvas);
}
void VistaFigAgrandable::dibujar(Superficie *canvas,int xIni,int yIni){
	dibujar(canvas);
}

void VistaFigAgrandable::redraw(){
	
		int tempAncho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(1);
		if(orig==NULL || tempAncho!= escalaAnterior){
			delete orig;
			Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->getID()));
			orig = temp->scaleImagen(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->getDimension()->getAncho()/fig->getLargo()),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->getDimension()->getAlto()));
			escalaAnterior = tempAncho;
		}
		delete rotada;
		rotada = orig->rotarImagen(fig->getDimension()->getAngulo());
	if (fig->traslucido) rotada->setTransparency(150);
}