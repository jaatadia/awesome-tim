#pragma once
#include "FiguraCompuesta.h"

#include "Dimension.h"
#include "Circulo.h"
#include "Cuadrado.h"

class CarroAtable : public FiguraCompuesta {

private:
	Figura* tabla;
	Figura* circIzq;
	Figura* circDer;
	
	bool atadoDerecha;
	bool atadoIzquierda;

public:

	CarroAtable(double posX, double posY);	//pos de la tabla!
	~CarroAtable(void);
	static void calcularPosPuntas(double& posXizq,double& posXder, double& posYizq, double& posYder, double posX_Tabla, double posY_Tabla, double angulo, double angulo1, double angulo2);
	void shift();

	Figura* clonar();
	int getTipoDimension();
	int getTipoFigura();

	//se le pasa la poicion en la que esta queriendo atar y devuelve el numero de posicion atable mas cercano(-1 es que no habia)
	virtual int esAtableSoga(double x,double y);
	//se le pasa un numero de posicion atable y devuelve la posicion x e y de donde se ata por mas que ya este atado
	virtual void posAtableSoga(int numero,double* x,double* y);
	virtual void atarSoga(int numero);//le dice que ate una soga en su pocicion atable numero
	virtual void desatarSoga(int numero);//le dice que desate una soga de su posicion atable numero
	
	Figura* getTabla();
	Figura* getPuntaIzq();
	Figura* getPuntaDer();

};
