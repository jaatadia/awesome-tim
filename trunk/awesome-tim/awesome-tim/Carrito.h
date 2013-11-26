#pragma once
#include "FiguraCompuesta.h"
#include "Box2D/Box2D.h"

#include "Dimension.h"
#include "Circulo.h"
#include "Cuadrado.h"
#include "CarroAtable.h"

class Carrito : public FiguraCompuesta {

private:
	CarroAtable* carro;
	Figura* ruedaIzq;
	Figura* ruedaDer;
	b2Body* b2dCuerpo;

	bool atado;

public:

	Carrito(double posX, double posY, double angulo);
	~Carrito(void);
	void calcularPosiciones(double& posXizq,double& posXder, double& posYizq,double& posYder, double& posX_Carro, double& posY_Carro, double posX, double posY);
	Figura* clonar();
	int getTipoDimension();
	int getTipoFigura();
	CarroAtable* getCarro();
	Figura* getRuedaIzq();
	Figura* getRuedaDer();

	//se le pasa la poicion en la que esta queriendo atar y devuelve el numero de posicion atable mas cercano(-1 es que no habia)
	virtual int esAtableSoga(double x,double y);
	//se le pasa un numero de posicion atable y devuelve la posicion x e y de donde se ata por mas que ya este atado
	virtual void posAtableSoga(int numero,double* x,double* y);
	virtual void atarSoga(int numero);//le dice que ate una soga en su pocicion atable numero
	virtual void desatarSoga(int numero);//le dice que desate una soga de su posicion atable numero

	void setCuerpo(b2Body* cuerpo);
	void actualizar();

	virtual bool tienePartesRotables(){return true;};
	virtual double getAnguloPartesRotables(){return ruedaIzq->getDimension()->getAngulo();};
	virtual void setAnguloPartesRotables(double angulo){
		this->ruedaIzq->setAngulo(angulo);
		this->ruedaDer->setAngulo(angulo);
	};
	
};
