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
	
	try{
		int calcX1;
		int calcY1;
		int calcX2;
		int calcY2;

		if(linea->getFigura1()){
			double x,y;
			linea->getFigura1()->posAtableCorrea(&x,&y);
			linea->setPunto1(x,y);
		}
		
		calcX1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x1));
		calcY1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y1));
			
		if(linea->getFigura2()){
			double x,y;
			linea->getFigura2()->posAtableCorrea(&x,&y);
			linea->setPunto2(x,y);
		}
		calcX2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->x2));
		calcY2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(((DLinea*)linea->getDimension())->y2));
		

		int calcAncho = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->ancho));

		
		if(simple){
			canvas->dibujarLinea(calcX1,calcY1,calcX2,calcY2,calcAncho,0,0,0);
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
		
	}catch(...){
		//std::cout<<"se produjo una falla\n\a";
	}
}
