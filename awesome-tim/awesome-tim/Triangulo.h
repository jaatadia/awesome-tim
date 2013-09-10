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
	double base;
	double altura;

private:
	static bool todos_positivos(double num1, double num2, double num3, double num4);
	static bool todos_negativos(double num1, double num2, double num3, double num4);
	static double sentido_circulacion(Posicion* A1,Posicion* A2,Posicion* A3);
	static bool orientaciones_iguales(double Origen,double circ1,double circ2,double circ3);
	static bool puntoPerteneceAlPerimetro(double x,double y);
	void recalcular_puntos_rotados(void);
	void crear_puntos_iniciales(void);
	void rotar_punto(Posicion* punto, double angulo);

public:
	Triangulo(double X, double Y, double angulo, double base, double altura);
	
	//No utilizar este constructr salvo para pruebas (no necesariamente el centro es real ya que no lo verifica)
	Triangulo(double X, double Y, double angulo, Posicion* punto1,Posicion* punto2,Posicion* punto3);
	
	~Triangulo(void);

	// Un punto pertenece al triangulo solo si esta en el interior de el. Si pertenece a su perimetro,
	// entonces no pertenece al triangulo :P
	bool puntoPertenece(double X, double Y);

	double getAncho(void);
	double getAlto(void);
	double getAngulo(void);
	void setAngulo(double ang);
};
