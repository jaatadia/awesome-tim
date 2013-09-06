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
	//agregar figura que se esta moviendo o rotando dentro del terreno

public:
	Terreno(int ancho,int alto);
	~Terreno(void);

	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes* escalas);

	void setFondo(const char* img);

	void agregarFigura(Figura* fig);
	void rotarFigura(Figura* fig);
	void eliminarFigura(Figura* fig);

	void arrastrarFigura(double posClickX,double posClickY,double cantMovX,double cantMovY);


};
