#include "FiguraCircular.h"
#include "Circulo.h"

FiguraCircular::FiguraCircular(const char* ID,double radio,double pos_X,double pos_Y,int angulo):Figura(ID,new Circulo(radio,pos_X,pos_Y,angulo))
{
}

FiguraCircular::~FiguraCircular(void)
{
}
