#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"
#include <list>

/* terreno es el que contiene todas las figuras
y tiene las funciones necesarias para que le roten algun objeto le eliminen y dibuje todos los objetos en una superficie

mover una figura tambien?? 
*/

class Terreno: public Imprimible,public Validable,public Cambiable
{
private:
	int ancho,alto;
	Imagen* img;
	Superficie* sup;
	std::list<Figura*> figuras;

public:
	Terreno(int ancho,int alto);
	~Terreno(void);

	Superficie* getImpresion();

	void setFondo(Imagen* img);

	void agregarFigura(Figura* fig);
	void rotarFigura(Figura* fig);
	void eliminarFigura(Figura* fig);


};
