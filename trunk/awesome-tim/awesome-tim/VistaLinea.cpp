#include "VistaLinea.h"

VistaLinea::VistaLinea(Linea* lin):VistaFigura(lin)
{
	this->linea = lin;
}

VistaLinea::~VistaLinea(void)
{
}

void VistaLinea::dibujar(Superficie* canvas){
	int calcX1;
	int calcY1;
	int calcX2;
	int calcY2;

	if(linea->fig1){
		double x,y;
		linea->fig1->posAtableCorrea(&x,&y);
		linea->setPunto1(x,y);
	}
	calcX1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x1));
	calcY1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y1));
	
	if(linea->fig2){
		double x,y;
		linea->fig2->posAtableCorrea(&x,&y);
		linea->setPunto2(x,y);
	}
	calcX2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x2));
	calcY2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y2));
	

	int calcAncho = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->ancho));

	canvas->dibujarLinea(calcX1,calcY1,calcX2,calcY2,calcAncho);
}
