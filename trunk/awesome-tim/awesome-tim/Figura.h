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

private:
	
	Dimension* dimension;
//	Posicion pos;//las del cntro de la figura termino dentro de dimension
//	double angulo;// tambien dentro de dimension
	std::string ID;
	VistaFigura* myVista;
	bool traslucido;

public:
	Figura(const char* ID,Dimension* dim);
	~Figura(void);

	void cambiarPosicion(double Movx,double Movy);

	bool esMiPosicion(double x,double y);
	bool intersecaCon(double X1, double Y1, double X2, double Y2);

	void dibujarEnPixel(Superficie* super);
	void dibujar(Superficie* super);

	const char* getID();
	int getTipoDimension(){return dimension->getTipoDimension();};
	Dimension* getDimension();

	void setTraslucido(bool flag);
	void setAngulo(double angulo);

	Figura* clonar();//copia la figura

};
