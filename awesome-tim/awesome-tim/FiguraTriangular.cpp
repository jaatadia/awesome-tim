#include "FiguraTriangular.h"
#include "Triangulo2.h"

FiguraTriangular::FiguraTriangular(const char* ID,double X, double Y, double angulo, double base,double altura):Figura(ID,new Triangulo2(X,Y,angulo,base,altura))
{
}

FiguraTriangular::~FiguraTriangular(void)
{
}
