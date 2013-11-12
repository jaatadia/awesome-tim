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
			double x1,y1;
			linea->getPunto1(&x1,&y1);
			calcX1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x1));
			calcY1 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y1));

			double x2,y2;
			linea->getPunto2(&x2,&y2);
			calcX2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x2));
			calcY2 = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y2));
		
		
			calcAncho = int(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(((DLinea*)linea->getDimension())->ancho));

			if(simple){
				canvas->dibujarLinea(calcX1,calcY1,calcX2,calcY2,calcAncho,193,154,107);
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
			std::cout<<"\a\n";
		}
}
