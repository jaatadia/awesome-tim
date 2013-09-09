#pragma once

#include "ErrorLogHandler.h"
#include "Dimension.h"
#include "Posicion.h"

class Triangulo: public Dimension
{
private:
	Posicion* A1;
	Posicion* A2;
	Posicion* A3;
	double centroX;
	double centroY;
	double angulo;

private:
	static bool todos_positivos(double num1, double num2, double num3, double num4);
	static bool todos_negativos(double num1, double num2, double num3, double num4);
	static double sentido_circulacion(Posicion* A1,Posicion* A2,Posicion* A3);
	static bool orientaciones_iguales(double Origen,double circ1,double circ2,double circ3);

public:
	Triangulo(double X, double Y, double angulo, Posicion* punto1, Posicion* punto2, Posicion* punto3);
	~Triangulo(void);

	bool puntoPertenece(double X, double Y);

};
