#include "Segmento.h"

Segmento::Segmento(double X1, double Y1, double X2, double Y2) : Recta(X1, Y1, X2, Y2)
{
	if (X1<=X2){
		XMin = X1;
		XMax = X2;
	}else{
		XMin = X2;
		XMax = X1;
	}

	if (Y1<=Y2){
		YMin = Y1;
		YMax = Y2;
	}else{
		YMin = Y1;
		YMax = Y2;
	}

	XInicial = X1;
	XFinal = X2;
	YInicial = Y1;
	YFinal = Y2;
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

bool Segmento::intersecaCon(Segmento* otroSegmento){

	Recta recta1(this->getXInicial(),this->getYInicial(),this->getXFinal(),this->getYFinal());
	Recta recta2(otroSegmento->getXInicial(),otroSegmento->getYInicial(),otroSegmento->getXFinal(),otroSegmento->getYFinal());

	if ( recta1.getPendiente() == recta2.getPendiente() ){
		//chequeo rango de X
		if (this->getXMax() >= otroSegmento->getXMin()){
			return this->intersecaCon(&recta2);
		}
	}else{
		return ( this->intersecaCon(&recta2) || otroSegmento->intersecaCon(&recta1) );
	}

	return false;
}