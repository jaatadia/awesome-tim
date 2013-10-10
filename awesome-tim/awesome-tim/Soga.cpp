#include "Soga.h"


Soga::Soga(const char* ID = ImgSegmSoga,Dimension* dim = NULL):Figura("",dim)
{

//	largoEstirada = dim->getAncho();
//	/*como las cosas solapan le agrego un 10 % para crearla*/
//	double largoExtra = largoEstirada * 1.1;
//
//	/*crear los segmentos. Los pongo ligeramente solapados para unirlos!*/
//
//	double inicioSoga = dim->getX() - ( dim->getAncho()/2.f ) + ( LARGO_SEGMENTO_SOGA / 2.f );
//	double alturaSoga = dim->getY() ;
//
//	Figura* segm = NULL;
//	Dimension* dimSegm = NULL;
//
//	int i = 0;
//	for ( i ; i*LARGO_SEGMENTO_SOGA < largoExtra ; i++){
//
//		dimSegm = new Cuadrado(LARGO_SEGMENTO_SOGA, ALTO_SEGMENTO_SOGA, i*LARGO_SEGMENTO_SOGA + inicioSoga-0.1*i/*"-0.1" para solapar*/, alturaSoga, dim->getAngulo());
//		segm = new Figura(ID,dimSegm);
//		
//		segm->setCambio(true);
//		segm->setTraslucido(false);
//		
//		partesFigura.push_back(segm);
//	}
//
//	/*agrego el ultimo segmento variable. (Si es necesario.)*/
//
//	if ((largoExtra - (i*LARGO_SEGMENTO_SOGA)) > 0){
//		dimSegm = new Cuadrado(ALTO_SEGMENTO_SOGA, largoExtra - (i*LARGO_SEGMENTO_SOGA), i*LARGO_SEGMENTO_SOGA + inicioSoga -1*i, dim->getY(), dim->getAngulo());
//		segm = new Figura(ID,dimSegm);
//
//		segm->setCambio(true);
//		segm->setTraslucido(false);
//			
//		partesFigura.push_back(segm);
//	}
//
//	//seteo angulos correspondientes (ver figuraCompuesta.h y su constructor)
//	this->inicAngulosCentro();
//
//	//pongo todos los locales en cero
//
//	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
//		angulos.push_back(0.f);
//	}
//
}

Soga::~Soga(void)
{}


/*copia la figura*/
Figura* Soga::clonar(){

	/*Figura* seg = partesFigura.front();
	const char* id = seg->getID();
		
	Figura* figADevolver = new Soga(id,this->dimension->clonar());

	return figADevolver;*/

	return NULL;
}