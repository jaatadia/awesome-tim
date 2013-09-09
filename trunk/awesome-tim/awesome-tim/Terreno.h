#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "Figura.h"
#include <list>

/* terreno es el que contiene todas las figuras
y tiene las funciones necesarias para que le roten algun objeto le eliminen y dibuje todos los objetos en una superficie
*/

class Terreno: public Imprimible,public Cambiable
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

	//NOta para mi mismo: considerar como unir estos tres tienen demasiado codigo en comun
	//respuesta metodo privada Figura* buscarFigura(double posX, double posY);
	void rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY);
	void arrastrarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY);
	void borrarFigura(double posClickX, double posClickY);

	void soltarFigura();

	int getAncho();
	int getAlto();

private:
	bool hayFiguras();

};
