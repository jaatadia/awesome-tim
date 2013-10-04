#include "Botonera.h"

Botonera::Botonera(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	this->x = this->y = 0;
	this->alturaMax = 0;
	this->alturaMaxOrig = alturaMax;
}

void Botonera::agregarBoton(Figura * figura, int cantidadInstancias) {
	std::map<Figura *, int> mapa;
	mapa[figura] = cantidadInstancias;
	this->lstFiguras.push_back(mapa);
}

Figura * Botonera::obtenerFigura(int numeroFigura){
	Figura * retorno = 0;
	bool encontrada = false;

	std::list<map<Figura *, int>>::iterator itFig = this->lstFiguras.begin();
	for (int i = 0; itFig != this->lstFiguras.end(); i++)
	{
		if (i == numeroFigura){
			encontrada = true;
			break;
		}
		++itFig;
	}
	if (encontrada){
		//if (((std::map<Figura*,int>::iterator)((*itFig).begin()))->second) {
			retorno = (((std::map<Figura*,int>::iterator)((*itFig).begin()))->first)->clonar();
			//--(((std::map<Figura*,int>::iterator)((*itFig).begin()))->second);
			retorno->setTraslucido(true);
		//}
	}
	
	return retorno;
}

void Botonera::restaurarInstanciaActual( int numeroFigActual ){

	std::list<map<Figura *, int>>::iterator itFig = this->lstFiguras.begin();
	
	for (int i = 0; itFig != this->lstFiguras.end(); i++)
	{
		if (i == numeroFigActual){
			++(((std::map<Figura*,int>::iterator)((*itFig).begin()))->second);
			break;
		}
		++itFig;
	}

}

Botonera::~Botonera() {
	std::list<map<Figura *, int>>::iterator itFig;
	for (itFig = this->lstFiguras.begin(); itFig != this->lstFiguras.end(); itFig++)
	{
		delete (((std::map<Figura*,int>::iterator)((*itFig).begin()))->first);
	}

}

std::list<map<Figura *, int>> Botonera::getListaFiguras() {
	return this->lstFiguras;
}
