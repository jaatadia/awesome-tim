#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"
#include <list>

/* terreno es el que contiene todas las figuras
y tiene las funciones necesarias para que le roten algun objeto le eliminen y dibuje todos los objetos en una superficie
*/

class Terreno: public Imprimible,public Validable,public Cambiable
{
private:
	int ancho,alto;
	Imagen* img;
	Superficie* sup;
	std::list<Figura*> figuras;
	Figura* figuraActiva; // se mantiene separada la que se esta arrastrando o girando

public:
	Terreno(int ancho,int alto);
	~Terreno(void);

	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes* escalas);

	void setFondo(const char* img);

	void agregarFigura(Figura* fig);
	void eliminarFigura(Figura* fig);

	//NOta para mi mismo: considerar como unir estos dos tienen demasiado codigo en comun	
	void rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY);
	void arrastrarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY);

	void soltarFigura();

private:
	bool hayFiguras();

};
