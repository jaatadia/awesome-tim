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

	//cambia el angulo sumandole el que hay entre los vectores desde el centro de la figura hasta donde le pasas
	void cambiarAngulo(double XVector1,double YVector1,double XVector2,double YVector2);

	bool esMiPosicion(double x,double y,EscalasDeEjes* escalas);
	bool intersecaCon(double X1, double Y1, double X2, double Y2);

	void dibujarEnPixel(Superficie* super,EscalasDeEjes* escalas);
	void dibujar(Superficie* super,EscalasDeEjes* escalas);

	const char* getID();
	int getTipoDimension(){return dimension->getTipoDimension();};
	Dimension* getDimension();

	void setTraslucido(bool flag);

	Figura* clonar();//copia la figura

private:
	//defino positivo en sentido horario
	bool anguloEsPositivo(double X1, double Y1, double X2, double Y2); 
	//respecto del centro de la figura por supuesto, y recordar que el eje y apunta hacia abajo
	int obtenerCuadranteDeClick(double X, double Y);
};
