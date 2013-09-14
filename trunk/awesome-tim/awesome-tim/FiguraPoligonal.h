#pragma once

#include "Figura.h"
#include "Constantes.h"

class FiguraPoligonal: public Figura
{
public:
	FiguraPoligonal(const char* ID,double x, double y,double radio,int vertices,double angulo);
	~FiguraPoligonal(void);

	int getTipoDimension(){return POLIGONOREGULAR;};
};
