#include "Segmento.h"

Segmento::Segmento(double X1, double Y1, double X2, double Y2) : Recta(X1, Y1, X2, Y2)
{
	XInicial = X1;
	XFinal = X2;
}

Segmento::~Segmento(void)
{
}

bool Segmento::intersecaCon(Segmento* otroSgmt){

	bool algunoVertical,paralelos;

	algunoVertical = ( this->vertical() == true ) || ( otroSgmt->vertical() == true);
	paralelos = ( this->getPendiente() == otroSgmt->getPendiente() );

//si alguno vertical
//si ambos horizontales
//el caso bonito
	if ( !paralelos && !algunoVertical ){

		double xInterseccion;
		double restaOrdenadas = otroSgmt->getOrdenadaAlOrigen() - this->getOrdenadaAlOrigen();
		double restaPendientes =  - otroSgmt->getPendiente() + this->getPendiente();

		xInterseccion = restaOrdenadas/restaPendientes;

		if ((xInterseccion < XFinal) && (xInterseccion > XInicial))
			return true;

		return false;
	}
	else{
		if (paralelos){
			return ( this->getOrdenadaAlOrigen() == otroSgmt->getOrdenadaAlOrigen() );
		}
		else
			if (algunoVertical){
				if (this->vertical()){
					return (otroSgmt->getX() <= this->getXFinal()) && ( otroSgmt->getX() <= this->getXInicial());
				}else
				{
					return (otroSgmt->getX() <= this->getXFinal()) && ( otroSgmt->getX() <= this->getXInicial());
				}
			}
	}
}
