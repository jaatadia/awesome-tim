#include "VistaPedacitoSoga.h"

VistaPedacitoSoga::VistaPedacitoSoga(PedacitoSoga* pedacito):VistaFigura(pedacito){
	this->pedacito = pedacito;
}

void VistaPedacitoSoga::dibujar(Superficie* canvas){
		int calcX1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(pedacito->px1));
		int calcY1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(pedacito->py1));
		int calcX2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(pedacito->px2));
		int calcY2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(pedacito->py2));
		int ancho;
		if(calcX2 > calcX1) ancho = calcX2-calcX1;
		else ancho = calcX1-calcX2;
		canvas->dibujarLinea(calcX1,calcY1,calcX1,calcY2,ancho,193,154,107);
		//canvas->dibujarLinea(calcX1,calcY1,calcX2,calcY2,10,0,0,0);
}