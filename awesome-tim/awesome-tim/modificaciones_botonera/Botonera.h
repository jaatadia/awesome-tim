#ifndef __BOTONERA_H__
#define __BOTONERA_H__

#include <iostream>
#include <list>
#include "Rectangulo.h"
#include "Figura.h"

using namespace std;
class Figura;

class Botonera
{
private:
	int x, y, ancho, alto, indice, anchoBoton, altoBoton, alturaMax;
	std::list<int> lstFiguras;
	std::list<int> instanciasFiguras;

public:
	// Maty <
	//static const int TRIANGULO = 0;
	//static const int CUADRADO  = TRIANGULO + 1;
	//static const int CIRCULO   = CUADRADO + 1;
	// Maty > -- Esto deberia ir en alguna otra parte

	Botonera(int ancho,int alto);
	~Botonera(void);

	Figura * obtenerFigura(int numFigura);

	// Getters
	int getX(){return this->x;}
	int getY(){return this->y;}
	int getAncho(){return this->ancho;}
	int getAlto(){return this->alto;}
	int getIndice(){return this->indice;}
	int getAnchoBoton(){return this->anchoBoton;}
	int getAltoBoton(){return this->altoBoton;}
	int getAlturaMax(){return this->alturaMax;}

	// Setters
	void setIndice(int indice) {this->indice = indice;}
	void setY(int y) {this->y = y;}
	void setAlturaMax(int alturaMax) {this->alturaMax = alturaMax;}
	void setAltoBoton(int altoBoton) {this->altoBoton = altoBoton;}

	void agregarBoton(int tipo, int cantidadInstancias);
};

#endif //__BOTONERA_H__