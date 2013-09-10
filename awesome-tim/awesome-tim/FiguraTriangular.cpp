#include "FiguraTriangular.h"
#include "Triangulo.h"

FiguraTriangular::FiguraTriangular(const char* ID,double X, double Y, double angulo, double base, double altura):Figura(ID,new Triangulo(X,Y,angulo,base,altura))
{
}

FiguraTriangular::~FiguraTriangular(void)
{
}
