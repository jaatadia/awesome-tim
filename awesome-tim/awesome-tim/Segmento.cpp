#include "Segmento.h"

Segmento::Segmento(double X1, double Y1, double X2, double Y2) : Recta(X1, Y1, X2, Y2)
{
	XInicial = X1;
	XFinal = X2;
	YInicial = Y1;
	YFinal = Y2;
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
		//si estan en rango del segmento
		if ((xInterseccion < XFinal) && (xInterseccion > XInicial) && (xInterseccion < otroSgmt->getXFinal()) && (xInterseccion > otroSgmt->getXInicial()) )
			return true;

		return false;
	}
	else{
		if (paralelos){
			//si se cruzan
			if (this->getOrdenadaAlOrigen() == otroSgmt->getOrdenadaAlOrigen() ){
				//si estan en rango del segmento
				if ((otroSgmt->getXInicial() < XFinal) && (XInicial < otroSgmt->getXFinal()) )
					return true;
		}
		else
			if (algunoVertical){
				//me fijo cual de los dos es vertical
				if (this->vertical()){
					//si se puede cruzar
					if ( getX() <= otroSgmt->getXFinal()) && ( getX() <= otroSgmt->getXInicial())
						//si esta en rango del segmento
						if ( (otroSgmt->getYInicial() < YFinal) && (YInicial < otroSgmt->getYFinal()))
							return true;
				}else
				{
					if (otroSgmt->getX() <= this->getXFinal()) && ( otroSgmt->getX() <= this->getXInicial())
						if ( (otroSgmt->getYInicial() < YFinal) && (YInicial < otroSgmt->getYFinal()))
							return true;
				}
			}
	}

	return false;
}
