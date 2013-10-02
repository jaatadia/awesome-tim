#pragma once

#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "Cambiable.h"
#include "VistaFigura.h"
#include "EscalasDeEjes.h"
#include <string>


class VistaFigura;

class Figura: public Dibujable,public Cambiable
{
public:
	friend class VistaFigura;

protected:
	Figura(){};	
	Dimension* dimension;
//	Posicion pos;//las del cntro de la figura termino dentro de dimension
//	double angulo;// tambien dentro de dimension
	std::string ID;
	VistaFigura* myVista;
	bool traslucido;

public:
	Figura(const char* ID,Dimension* dim);
	~Figura(void);

	virtual void cambiarPosicion(double Movx,double Movy);

	virtual bool esMiPosicion(double x,double y);
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual void dibujarEnPixel(Superficie* super);
	virtual void dibujar(Superficie* super);
	virtual void dibujar(Superficie* super,int xIni,int yIni);

	virtual const char* getID();
	virtual int getTipoDimension(){return dimension->getTipoDimension();};
	virtual Dimension* getDimension();

	virtual void setTraslucido(bool flag);
	virtual void setAngulo(double angulo);

	virtual Figura* clonar();//copia la figura

};
