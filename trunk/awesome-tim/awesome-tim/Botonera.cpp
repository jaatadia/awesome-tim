#include "Botonera.h"

Botonera::Botonera(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	this->x = this->y = 0;
	this->alturaMax = 0;
	this->indice = 0;
}

void Botonera::agregarBoton(int tipo, int cantidadInstancias) {
	this->lstFiguras.push_back(tipo);
	this->instanciasFiguras.push_back(cantidadInstancias);
}

Figura * Botonera::obtenerFigura(int numeroFigura){
	Figura * retorno = 0;
	std::list<int>::iterator itIns = this->instanciasFiguras.begin();
	std::list<int>::iterator itFig = this->lstFiguras.begin();
	for (int i = 0; itFig != this->lstFiguras.end(); i++)
	{
		if (i == numeroFigura)
			break;
		++itFig;
		++itIns;
	}
	if (*(itIns)) {
		switch (*(itFig)) {
			case TRIANGULO:
				//retorno = new Triangulo();
				cout << "triangulo" << endl;
				break;
			case CUADRADO:
				cout << "cuadrado" << endl;
				break;
			case CIRCULO:
				cout << "circulo" << endl;
				break;
		}
		--(*(itIns));
	}
	return retorno;
}

Botonera::~Botonera() {
	this->lstFiguras.clear();
}