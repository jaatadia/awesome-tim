#include "VistaLinea.h"

VistaLinea::VistaLinea(Linea* lin,bool flag):VistaFigura(lin)
{
	this->simple = flag;
	this->linea = lin;
}

VistaLinea::~VistaLinea(void)
{
}

void VistaLinea::dibujar(Superficie* canvas){
	
	
		int calcX1 = 10;
		int calcY1 = 10;
		int calcX2 = 10;
		int calcY2 = 10;
		int calcAncho = 10;

		try{
			if(linea->getFigura1()){
				double x,y;
				linea->posFigura1(&x,&y);
				linea->setPunto1(x,y);
			}
			calcX1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x1));
			calcY1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y1));

			if(linea->getFigura2()){
				double x,y;
				linea->posFigura2(&x,&y);
				linea->setPunto2(x,y);
			}
			calcX2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x2));
			calcY2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y2));
		
		
			calcAncho = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->ancho));
		}catch(...){
			
		}
		
		if(simple){
			canvas->dibujarLinea(calcX1,calcY1,calcX2,calcY2,calcAncho,100,30,30);
		}else{
			int desfasajeX;
			int desfasajeY;
			if(((calcX2>calcX1)&&(calcY1<calcY2))||((calcX2<calcX1)&&(calcY1>calcY2))){
				desfasajeX = calcAncho;
				desfasajeY = -calcAncho;
			}else{
				desfasajeX = calcAncho;
				desfasajeY = calcAncho;
			}
			canvas->dibujarLinea(calcX1+desfasajeX,calcY1+desfasajeY,calcX2+desfasajeX,calcY2+desfasajeY,calcAncho,0,0,0);
			canvas->dibujarLinea(calcX1-desfasajeX,calcY1-desfasajeY,calcX2-desfasajeX,calcY2-desfasajeY,calcAncho,0,0,0);
		}
}
