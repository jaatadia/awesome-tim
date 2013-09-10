#ifndef __BOTONERA_H__
#define __BOTONERA_H__

#include <iostream>
#include <list>
#include "Imprimible.h"
#include "Cambiable.h"
#include "Rectangulo.h"
#include "Figura.h"

using namespace std;
class Figura;

class Botonera: public Imprimible,public Cambiable
{
private:

	// Maty <
	//static const int TRIANGULO = 0;
	//static const int CUADRADO  = TRIANGULO + 1;
	//static const int CIRCULO   = CUADRADO + 1;
	// Maty > -- Esto deberia ir en alguna otra parte

	static const int FACTOR_SCROLL = 10;
	static const int SCROLL_TOP = 0;
	static const int SCROLL_BOT = SCROLL_TOP + 1;

	int x, y, ancho, alto, scrollStep, indice, anchoBoton, altoBoton, alturaMax, altoAreaScroll, altoAreaFiguras;
	bool scrollTop, scrollBot;
	Superficie * sup;
	Superficie * back;
	Superficie * supFiguraActual;
	Figura * figuraActual;
	std::list<int> lstFiguras;

public:
	Botonera(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras = 0.8);
	void agregarBoton(int tipo, Superficie * img);
	~Botonera(void);
	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes* escalas);

	void updateBotonera();
	Figura * obtenerFigura(double x, double y);
	void setScrollDirection(int direction);

};

#endif //__BOTONERA_H__