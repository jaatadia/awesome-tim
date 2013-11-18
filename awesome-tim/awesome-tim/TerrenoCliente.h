#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "Figura.h"
#include "Dimension.h"
#include "Constantes.h"
#include "Linea.h"
#include "Soga.h"
#include <string>
#include <list>
#include <vector>
#include "TransformFigureMessage.h"
#include "MaquinaEstados.h"

/* terreno es el que contiene todas las figuras
y tiene las funciones necesarias para que le roten algun objeto le eliminen y dibuje todos los objetos en una superficie
*/

class TerrenoCliente: public Imprimible,public Cambiable
{
public:
	double x1,y1,x2,y2;//puntos que definen el rectangulo donde se dibujar
private:
	int ex1,ey1,ex2,ey2;//puntos que definen como se dibuja dicho rectangulo
	int ancho,alto;
	Imagen* img;
	std::string fondoID;
	Imagen* fondo;
	Superficie* sup;
	std::list<Figura*> figuras;

	Figura* figuraActiva; // se mantiene separada la que se esta arrastrando o girando
	Posicion posAntFigActiva; 
	double angAntFigActiva;
	int largoAntFigActiva;
	bool fisicaActiva;

	int contEventosMov;

	MaquinaEstados* maq;
	int numCliente;

public:
	TerrenoCliente(int ancho,int alto,MaquinaEstados* maq,int numCliente,bool fisicaActiva=true);
	~TerrenoCliente(void);

	void setMiPorcion(double x1, double y1, double x2, double y2);

	Superficie* getImpresion();

	bool setFondo(const char* img);

	//devuelve true si se agrego bien, false si choca con algo
	bool agregarFigura(Figura* fig);
	void eliminarFigura(Figura* fig);


	void rotarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY);
	void arrastrarFigura(double posClickX, double posClickY, double cantMovX, double cantMovY,std::list<Figura*>* lista);
	//devuelve un vector con los tipos de las figuras borradas.
	std::vector<int> borrarFigura(double posClickX, double posClickY,Figura* vec[]);

	void buscarActiva(double posClickX ,double posClickY);
	void soltarFigura(bool ponerAunqueEsteAfueraDeLaZona = false);
	bool adentroZonaTerreno(double posX,double posY);

	int getAncho();
	int getAlto();
	std::string getFondo();
	std::list<Figura*> getListaFigs();

	void cambioVistaFiguras();

	void resizear();

	void actualizarModelo(Figura* vector[]); 

	void agrandarFigura();
	void achicarFigura();
	void shiftFigura();
	Figura* getFiguraAtableCorrea(double x,double y,bool soloMias);
	Figura* getFiguraAtableSoga(double x,double y,bool soloMias);

	bool posicionOcupada(Figura* figAPosicionar);

	void interactuar(double posClickX, double posClickY);

private:
	bool hayFiguras();
	Figura* buscarFigura(double posClickX, double posClickY,bool soloMias);
	void corregirPosicion(Figura* fig);
	void redraw();

	double calcularAngulo(Dimension* dim,double XVector1,double YVector1,double XVector2,double YVector2);
	int obtenerCuadranteDeClick(double X, double Y);
	bool anguloEsPositivo(double X1, double Y1, double X2, double Y2);

	bool posEnTerrenoExtendido(double posX,double posY);

	void borrarAtadura(Figura* fig);
};
