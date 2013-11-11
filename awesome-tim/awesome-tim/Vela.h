#pragma once
#include "figuracompuesta.h"

class Vela : public FiguraCompuesta {

private:
	Figura* velaCera;
	Figura* llama;

public:
	Vela(const char* id, double posX, double posY, double angulo);
	~Vela(void);

	void calcularPosLlama(double posX,double posY,double* posLlamaX,double* posLlamaY);
	Figura* clonar();
	int getTipoDimension();
	int getTipoFigura();
	Figura* getVelaCera();
	Figura* getLlama();
	bool cortaSoga();
	bool pinchaGlobo(Dimension* dim);
	virtual void getCuadradoCortante(double* x1,double* y1,double* x2,double* y2);

};
