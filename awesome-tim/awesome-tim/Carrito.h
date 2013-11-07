#pragma once
#include "FiguraCompuesta.h"

#include "Dimension.h"
#include "Circulo.h"
#include "Cuadrado.h"

class Carrito : public FiguraCompuesta {

private:
	Figura* carro;
	Figura* ruedaIzq;
	Figura* ruedaDer;
	
	bool atado;

public:

	Carrito(double posX, double posY, double angulo);
	~Carrito(void);
	void calcularPosiciones(double& posXizq,double& posXder, double& posYizq,double& posYder, double& posX_Carro, double& posY_Carro, double posX, double posY);
	Figura* clonar();
	int getTipoDimension();
	int getTipoFigura();
	Figura* getCarro();
	Figura* getRuedaIzq();
	Figura* getRuedaDer();
	int esAtableSoga(double x,double y);
	void posAtableSoga(int numero,double* x,double* y);
	void atarSoga(int numero);
	void desatarSoga(int numero);

};
