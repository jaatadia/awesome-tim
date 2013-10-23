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
	
};
