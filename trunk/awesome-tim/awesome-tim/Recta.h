#pragma once

/*
Por si el nombre no estuviese claro modela una recta L: y = m.x+b .
En el constructor le pasas 2 puntos de la recta en cuestion.
Los otros metodos sirven para saber si un punto esta por encima o por debajo de la recta.
Por encima o por debajo en el senitdo convencional (eje y para arriba).
Y el caso de que pertenezca a la recta esta incluido en el porDebajo porque se me canto hacerlo asi.
*/

class Recta
{
private:
	double pendiente,ordenadaAlOrigen;

public:
	Recta(double X1,double Y1,double X2,double Y2);
	~Recta(void);

	bool puntoPorDebajo(double X,double Y);
	bool puntoPorArriba(double X, double Y);
};
