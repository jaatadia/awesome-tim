#include "Segmento.h"

Segmento::Segmento(double X1, double Y1, double X2, double Y2) : Recta(X1, Y1, X2, Y2)
{
	if (X1<=X2){
		XInicial = X1;
		XFinal = X2;
	}else{
		XInicial = X2;
		XFinal = X1;
	}

	if (Y1<=Y2){
		YInicial = Y1;
		YFinal = Y2;
	}else{
		YInicial = Y1;
		YFinal = Y2;
	}
}

Segmento::~Segmento(void)
{
}


bool Segmento::intersecaCon(Recta* otraRecta){

	bool algunoVertical,paralelos;

	algunoVertical = ( this->vertical() == true ) || ( otraRecta->vertical() == true);
	paralelos = ( this->getPendiente() == otraRecta->getPendiente() );

//si alguno vertical
//si paralelos
//el caso bonito

	if (algunoVertical){
		//el segmento es vertical
		if (this->vertical()){
			if (otraRecta->puntoPorDebajo(XInicial,YInicial) && otraRecta->puntoPorArriba(XFinal,YFinal))
				return true;
		}else{//la recta es vertical
			if (otraRecta->puntoAIzquierda(XInicial,YInicial) && otraRecta->puntoADerecha(XFinal,YFinal))
				return true;
		}
		return false;
	}else
		//paralelos
		if (this->getPendiente() == otraRecta->getPendiente()){
			//incluyen al caso de que esta sobre la recta
			if ((otraRecta->puntoPorDebajo(XInicial,YInicial)) && (otraRecta->puntoPorArriba(XInicial,YInicial))){
				return true;
			}
		}else{//son diagonales bonitas

			if ( ((otraRecta->puntoPorDebajo(XInicial,YInicial)) && (otraRecta->puntoPorArriba(XFinal,YFinal))) ||
				((otraRecta->puntoPorDebajo(XFinal,YFinal))) && ((otraRecta->puntoPorArriba(XInicial,YInicial))) ){
				return true;
			}else{
				return false;
			}
		}

	return false;
}