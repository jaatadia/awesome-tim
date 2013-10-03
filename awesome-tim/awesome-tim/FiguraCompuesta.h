#pragma once

#include "Figura.h"
#include "Constantes.h"

#include <list>

class FiguraCompuesta :	public Figura{

protected:

	std::list<Figura*> partesFigura;

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
};
