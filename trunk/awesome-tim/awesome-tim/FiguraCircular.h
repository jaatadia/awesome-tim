#pragma once

#include "Figura.h"

class FiguraCircular: public Figura
{
public:
	FiguraCircular(const char* ID,double radio,double pos_X,double pos_Y,int angulo);
	~FiguraCircular(void);
	
	int getTipoDimension(){return CIRCULO;};
};
