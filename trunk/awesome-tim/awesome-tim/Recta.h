#pragma once

/*
Por si el nombre no estuviese claro modela una recta L: y = m.x+b .
En el constructor le pasas 2 puntos de la recta en cuestion.
Los otros metodos sirven para saber si un punto esta por encima o por debajo de la recta.

Por encima o por debajo en el sentido convencional (eje y para arriba). Preguntar solo si la recta NO es vertical.

Preguntar si esta a izq o a der solo si la recta es vertical.
*/

class Recta
{
private:
	bool esVertical;
	double x;
	double pendiente,ordenadaAlOrigen;

public:
	Recta(double X1,double Y1,double X2,double Y2);
	virtual ~Recta(void);

	bool puntoPorDebajo(double X,double Y);
	bool puntoPorArriba(double X, double Y);

	bool puntoADerecha(double X,double Y);
	bool puntoAIzquierda(double X,double Y);

	double getPendiente(){return pendiente;};
	double getOrdenadaAlOrigen(){return ordenadaAlOrigen;};
	double getX(){return x;};

	bool vertical(){return esVertical;};
	bool horizontal(){ return (pendiente == 0);};
};
