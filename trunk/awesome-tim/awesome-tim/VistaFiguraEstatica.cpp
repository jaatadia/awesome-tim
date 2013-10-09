#include "VistaFiguraEstatica.h"

VistaFiguraEstatica::VistaFiguraEstatica(Figura* fig,const char* ID)
{
	this->fig = fig;
	this->ID = ID;
	escalaAnterior = -1;
	this->rotada = NULL;
}

VistaFiguraEstatica::~VistaFiguraEstatica(void)
{
	delete rotada;
}

void VistaFiguraEstatica::dibujar(Superficie *sup){
	if (this->fig->huboCambios()||(rotada==NULL)){
		redraw();
	}
	
	int calcX = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->getDimension()->getX()) - rotada->getAncho()/2.0);
	int calcY = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->getDimension()->getY()) - rotada->getAlto()/2.0);

	sup->dibujarImagen(rotada,NULL,calcX,calcY);
}

void VistaFiguraEstatica::redraw(){
	
	int tempAncho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(fig->getDimension()->getAncho());
	if(rotada==NULL || tempAncho!= escalaAnterior){
		delete rotada;
		Imagen* temp = (Imagen*)(Contenedor::getMultimedia(ID));
		rotada = temp->scaleImagen(tempAncho,int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(fig->getDimension()->getAlto())));
		escalaAnterior = tempAncho;
	}
	
	if(fig->traslucido) rotada->setTransparency(150);
	else rotada->setTransparency(255);
}