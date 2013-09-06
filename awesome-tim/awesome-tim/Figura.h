#pragma once


#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "Cambiable.h"
#include "VistaFigura.h"
#include "EscalasDeEjes.h"

class VistaFigura;

class Figura: public Dibujable,public Cambiable
{
public:
	friend class VistaFigura;

private:
	
	Dimension* dimension;
//	Posicion pos;//las del cntro de la figura termino dentro de dimension
//	double angulo;// tambien dentro de dimension
	const char* ID;
	VistaFigura* myVista;

public:
	Figura(const char* ID,Dimension* dim);
	~Figura(void);

	void cambiarPosicion(double x,double y);
	bool esMiPosicion(double x,double y);

	void dibujarEnPixel(Superficie* super,EscalasDeEjes* escalas);
	void dibujar(Superficie* super,EscalasDeEjes* escalas);
};
