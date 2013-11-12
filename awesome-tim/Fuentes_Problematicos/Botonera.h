#ifndef __BOTONERA_H__
#define __BOTONERA_H__

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "Rectangulo.h"
#include "Figura.h"
#include "Constantes.h"

using namespace std;

class Botonera
{
private:
	int x, y, ancho, alto, anchoBoton, altoBoton, alturaMax;
	int alturaMaxOrig;
	std::list<map<Figura *, int>> lstFiguras;

public:

	Botonera(int ancho,int alto);
	~Botonera(void);

	Figura * obtenerFigura(int numFigura);
	void restaurarInstanciaActual( int numeroFigActual );
	void restaurarInstancias( std::vector<int> numsFigARestaurar );

	// Getters
	int getX(){return this->x;}
	int getY(){return this->y;}
	int getAncho(){return this->ancho;}
	int getAlto(){return this->alto;}
	int getAnchoBoton(){return this->anchoBoton;}
	int getAltoBoton(){return this->altoBoton;}
	int getAlturaMax(){return this->alturaMax;}
	int getAlturaMaxOrig(){return this->alturaMaxOrig;}
	std::list<map<Figura *, int>> getListaFiguras();

	// Setters
	void setY(int y) {this->y = y;}
	void setAlturaMax(int alturaMax) {this->alturaMax = alturaMax;}
	void setAlturaMaxOrig(int alturaMax) {this->alturaMaxOrig = alturaMax;}
	void setAltoBoton(int altoBoton) {this->altoBoton = altoBoton;}
	void setAnchoBoton(int anchoBoton) {this->anchoBoton = anchoBoton;}
	void setAlto(int alto){this->alto=alto;};
	void setAncho(int ancho){this->ancho=ancho;};

	void agregarBoton(Figura * figura, int cantidadInstancias);
};

#endif //__BOTONERA_H__