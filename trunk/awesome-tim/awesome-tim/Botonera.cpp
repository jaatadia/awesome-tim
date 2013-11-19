#include "Botonera.h"

Botonera::Botonera(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	this->x = this->y = 0;
	this->alturaMax = 0;
	this->alturaMaxOrig = alturaMax;
}

void Botonera::agregarBoton(Figura * figura, int cantidadInstancias) {
	struct boton mapa;
	mapa.figura = figura;
	mapa.cantInstancias = cantidadInstancias;
	this->lstFiguras.push_back(mapa);
}

Figura * Botonera::obtenerFigura(int numeroFigura){
	Figura * retorno = 0;
	bool encontrada = false;

	std::list<struct boton>::iterator itFig = this->lstFiguras.begin();
	for (int i = 0; itFig != this->lstFiguras.end(); i++)
	{
		if (i == numeroFigura){
			encontrada = true;
			break;
		}
		++itFig;
	}
	if (encontrada){ 
		if ((*itFig).cantInstancias!=0) {    //para q funcione lo de la cant de instancias
			retorno = (*itFig).figura->clonar();
			(*itFig).cantInstancias -= 1;
			retorno->setTraslucido(true);
		}
	}
	
	return retorno;
}

void Botonera::restaurarInstanciaActual( int numeroFigActual ){

	std::list<struct boton>::iterator itFig = this->lstFiguras.begin();
	
	for (int i = 0; itFig != this->lstFiguras.end(); i++)
	{
		if (i == numeroFigActual){
			(*itFig).cantInstancias += 1;
			break;
		}
		++itFig;
	}
}

void Botonera::restaurarInstancias( std::list<int> numsFigARestaurar ){
	
	int i = 0;
	int tipoFig = -1;
	std::list<struct boton>::iterator itFig;
	Figura* figBotonera = NULL;

	for (std::list<int>::iterator it = numsFigARestaurar.begin();it != numsFigARestaurar.end();it++){
		tipoFig = (*it);
		
		for (itFig = this->lstFiguras.begin(); itFig != this->lstFiguras.end(); ++itFig)
		{
			figBotonera = (*itFig).figura;
			if (figBotonera->getTipoFigura() == tipoFig){
				(*itFig).cantInstancias += 1;
				break;
			}
		}
	}
}

Botonera::~Botonera() {
	std::list<struct boton>::iterator itFig;
	for (itFig = this->lstFiguras.begin(); itFig != this->lstFiguras.end(); itFig++)
	{
		delete (*itFig).figura;
	}

}

std::list<struct boton> Botonera::getListaFiguras() {
	return this->lstFiguras;
}
