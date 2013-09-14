#include "FiguraCuadrada.h"
#include "Cuadrado.h"

FiguraCuadrada::FiguraCuadrada(const char* ID,double ancho,double alto,double X,double Y, double angulo):Figura(ID,new Cuadrado(ancho,alto,X,Y,angulo))
{
}

FiguraCuadrada::~FiguraCuadrada(void)
{
}

//Cuadrado* FiguraCuadrada::getDimension(){
//	return (Cuadrado*)  Figura::getDimension();
//}