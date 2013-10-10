#pragma once
#include "FiguraCompuesta.h"

#include "Dimension.h"
#include "Circulo.h"
#include "Cuadrado.h"

//#define CANT_ELEM_BALANCIN 4

class Balancin :
	public FiguraCompuesta
{

private:
	Figura* tabla;
	Figura* circIzq;
	Figura* circDer;
	
	bool atadoDerecha;
	bool atadoIzquierda;

public:

	//Balancin(double posX, double posY, double angulo,std::list<Figura*> listaFiguras); 
	Balancin(const char* ID,double posX, double posY, double angulo);	//la pos es la del centro de la tabla!
	~Balancin(void);
	static void calcularPosPuntas(double* posXizq,double* posXder, double* posY, double posX_Tabla, double posY_Tabla);
	bool atar(double posX, double posY);
	bool desatar(double posX, double posY);
	bool esAtable(double* posX, double* posY);

	Figura* clonar();
	int getTipoDimension();
	int getTipoFigura();

//	bool choqueConFigura(Figura* fig);
};
