#include "Soga.h"


Soga::Soga(const char* ID,Dimension* dim):FiguraCompuesta("",dim)
{

	largoEstirada = dim->getAncho();

	//crear los segmentos.

	Figura* segm = NULL;
	Dimension* dimSegm = NULL;

	int i = 0;
	for ( i = 0; i*LARGO_SEGMENTO_SOGA < dim->getAncho() ; i++){
		
		dimSegm = new Cuadrado(LARGO_SEGMENTO_SOGA, ALTO_SEGMENTO_SOGA, i*LARGO_SEGMENTO_SOGA + dim->getX(), dim->getY(), dim->getAngulo());
		segm = new Figura(ID,dimSegm);
		
		segm->setCambio(true);
		segm->setTraslucido(false);
		
		partesFigura.push_back(segm);
	}

	//agrego el ultimo segmento variable. (Si es necesario.)

	if ((largoEstirada - (i*LARGO_SEGMENTO_SOGA)) != 0){
		dimSegm = new Cuadrado(ALTO_SEGMENTO_SOGA, largoEstirada - (i*LARGO_SEGMENTO_SOGA), i*LARGO_SEGMENTO_SOGA + dim->getX(), dim->getY(), dim->getAngulo());
		segm = new Figura(ID,dimSegm);

		segm->setCambio(true);
		segm->setTraslucido(false);
			
		partesFigura.push_back(segm);
	}
}

Soga::~Soga(void)
{}


//copia la figura
Figura* Soga::clonar(){

	Figura* figADevolver = new Soga("",this->dimension->clonar());

	return figADevolver;
}