#include "FiguraPoligonal.h"
#include "PoligonoRegular.h"

FiguraPoligonal::FiguraPoligonal(const char* ID,double x, double y,double radio,int vertices,double angulo):Figura(ID,new PoligonoRegular(x,y,radio,vertices,angulo))
{
}

FiguraPoligonal::~FiguraPoligonal(void)
{
}
