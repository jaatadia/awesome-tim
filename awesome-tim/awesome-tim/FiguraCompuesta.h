#pragma once

#include "Figura.h"
#include "Constantes.h"
#include <math.h>

#include <list>

class FiguraCompuesta :	public Figura{

protected:

	std::list<Figura*> partesFigura;
	std::list<double> angulos; //los angulos iniciales de cada figura componente respecto de su centro local
							   //empieza en cero
	std::list<double> angulosCentroIniciales; //los angulos de cada figura componente respecto del centro del grupo 
	std::list<double> angulosCentroActuales;


	std::list<Figura*>::iterator iterFig;

	//no tiene ID
	//Dimension es un cuadrado
	//no tiene vista 

public:
	FiguraCompuesta(const char* ID, Dimension* dim);
	~FiguraCompuesta(void);

	virtual void cambiarPosicion(double Movx,double Movy);

	virtual bool esMiPosicion(double x,double y);
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual void dibujarEnPixel(Superficie* super);
	virtual void dibujar(Superficie* super);
	virtual void dibujar(Superficie* super,int xIni,int yIni);

	virtual int getTipoDimension()=0;

	virtual void setTraslucido(bool flag);
	virtual void setAngulo(double angulo);

	virtual Figura* clonar()=0;//copia la figura

	//para este no devuelve nada valido (vacio)
	virtual const char* getID();

	//para este devuelve un cuadrado que contiene a la figura
	virtual Dimension* getDimension();

	virtual std::list<Figura*> getFigurasComp(){return partesFigura;};

protected:

	void inicAngulosCentro();
//s�, los saque tal cual del terreno, s�, deberian estar en un clase aparte tipo "CosasDeGeometria" y s� pienso hacerlo 
//en algun momento

private:
	double calcularAngulo(Dimension* dim, double XVector1,double YVector1,double XVector2,double YVector2);
	int obtenerCuadranteDeClick(double X, double Y);
	bool anguloEsPositivo(double X1, double Y1, double X2, double Y2);
};
