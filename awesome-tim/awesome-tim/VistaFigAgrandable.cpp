#include "VistaFigAgrandable.h"

VistaFigAgrandable::VistaFigAgrandable(Figura* fig){
	this->fig = fig;
	this->orig = NULL;
	this->rotada = NULL;
	this->escalaAnterior = 0;
	this->largo_anterior = -1;
	this->imggrande = NULL;
}

VistaFigAgrandable::~VistaFigAgrandable(void){
	delete imggrande;
}
void VistaFigAgrandable::redraw(){
	
	int tempAncho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(1);
	if(orig==NULL || tempAncho!= escalaAnterior){
		delete orig;
		Imagen* temp = (Imagen*)(Contenedor::getMultimedia(fig->getID()));
		orig = temp->scaleImagen(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->getDimension()->getAncho()/fig->getLargo()),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->getDimension()->getAlto()));
		escalaAnterior = tempAncho;
		largo_anterior = -1;
	}

	if (largo_anterior != fig->getLargo()){
		delete imggrande;
		imggrande = new Imagen((orig->getAncho())*(this->fig->getLargo()),orig->getAlto());
		Uint32 aux = imggrande->atransparentar();
		largo_anterior = fig->getLargo();

		for(int i=0;i<fig->getLargo();i++){
			imggrande->dibujarImagen(orig,NULL,i*orig->getAncho(),0);
		}
		imggrande->atransparentar(aux);
	}

	delete rotada;
	rotada = imggrande->rotarImagen(fig->getDimension()->getAngulo());
	
	if (fig->traslucido) rotada->setTransparency(150);
	if(fig->superpuesta) rotada->pintarRojo();
}