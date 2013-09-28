#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "Figura.h"
#include "Dimension.h"
#include "Constantes.h"
#include "Box2DWorld.h"
#include <string>
#include <list>

/* terreno es el que contiene todas las figuras
y tiene las funciones necesarias para que le roten algun objeto le eliminen y dibuje todos los objetos en una superficie
*/

class Terreno: public Imprimible,public Cambiable
{
private:
	int ancho,alto;
	Imagen* img;
	Imagen* fondo;
	Superficie* sup;
	std::list<Figura*> figuras;
	Figura* figuraActiva; // se mantiene separada la que se esta arrastrando o girando
	std::string fondoID;
	Box2DWorld * mundoBox2D;
	bool fisicaActiva;

public:
	Terreno(int ancho,int alto,bool fisicaActiva=true);
	~Terreno(void);

	Superficie* getImpresion();

	bool setFondo(const char* img);

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
	std::string getFondo();
	std::list<Figura*> getListaFigs();

	void cambioVistaFiguras();

	void resizear();

	void buscarActiva(double posClickX ,double posClickY);

	bool huboCambios();

	void actualizarModelo(); 

private:
	bool hayFiguras();
	Figura* buscarFigura(double posClickX, double posClickY);
	void corregirPosicion(Figura* fig);
	void redraw();
	double calcularAngulo(Figura* fig,double XVector1,double YVector1,double XVector2,double YVector2);

	int obtenerCuadranteDeClick(double X, double Y);
	bool anguloEsPositivo(double X1, double Y1, double X2, double Y2);
};
