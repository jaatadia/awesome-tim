#include "Recta.h"

Recta::Recta(double X1,double Y1,double X2,double Y2){

	pendiente = (Y1-Y2)/(X1-X2);
	ordenadaAlOrigen = Y1 - pendiente * X1; 

	esVertical = false;
	x = 0;

	if (X1-X2 == 0){
		esVertical = true;
		x = X1;
	}
}

Recta::~Recta(void){
}

bool Recta::puntoPorDebajo(double X,double Y){

	return (Y >= pendiente*X + ordenadaAlOrigen);
}

bool Recta::puntoPorArriba(double X, double Y){

return !puntoPorDebajo(X,Y);
}

bool Recta::puntoADerecha(double X,double Y){
	return this->x <= X;
}

bool Recta::puntoAIzquierda(double X,double Y){
	return !puntoADerecha(X,Y);
}
