#pragma once
#include "FiguraCompuesta.h"

#define CANT_ELEM_BALANCIN 4

class Balancin :
	public FiguraCompuesta
{

private:
	Figura* tabla;
	Figura* punta1;
	Figura* punta2;
	Figura* base;
	const char* listaID[CANT_ELEM_BALANCIN];
	double posX;
	double posY;

public:

	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	Balancin(Figura** figuras);
	void cambiarPosicion(double x,double y);
	bool esMiPosicion(double x,double y);
	void dibujar(Superficie* super);
	const char** getListaDeIDs();
	bool intersecaCon(double X1, double Y1, double X2, double Y2);
	Figura* clonar();
	void setTraslucido(bool flag);
	void setAngulo(double angulo);
	~Balancin(void);

	virtual int getTipoFigura(){return BALANCIN;}
	virtual int getTipoDimension(){return CUADRADO;}

};
