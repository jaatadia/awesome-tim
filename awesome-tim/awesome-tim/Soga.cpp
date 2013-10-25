#include "Soga.h"


Soga::Soga(double x1,double y1,double x2, double y2,double ancho):Linea(ID_SOGA,true,x1,y1,x2,y2,ancho)
{
	num1=num2=-1;
}

Soga::~Soga(void){
	std::list<Figura*>::iterator iteradorLista;
	for (iteradorLista = segmentos.begin() ; iteradorLista != segmentos.end(); iteradorLista++){
			delete(*iteradorLista);
	}
}

/*copia la figura*/
Figura* Soga::clonar(){
	return new Soga(((DLinea*)dimension)->x1,((DLinea*)dimension)->y1,((DLinea*)dimension)->x2,((DLinea*)dimension)->y2,((DLinea*)dimension)->ancho);
}

Soga::Soga(DLinea* dim):Linea(ID_SOGA,dim)
{
	fig1=fig2=NULL;
	this->setCambio(true);
	puesto = false;
	simple = true;
}

bool Soga::choqueConFigura(Figura* fig){

	return false;
}

bool Soga::choqueConDimension(Dimension* dim){

	return false;
}

std::list<Figura*> Soga::getSegmentos(){
	return segmentos;
}

void Soga::putSegmento(Figura* fig){
	segmentos.push_back(fig);
}

bool Soga::meChoca(Dimension* dim){
		double x1,y1,x2,y2;
		getPunto1(&x1,&y1);
		getPunto2(&x2,&y2);

		double ox1 = dim->getX() - dim->getAncho()/2;
		double oy1 = dim->getY() - dim->getAlto()/2;
		double ox2 = dim->getX() + dim->getAncho()/2;
		double oy2 = dim->getY() + dim->getAlto()/2;

		double tempy1 = (y1<=y2) ? y1:y2;
		double tempy2 = (y1>y2) ? y1:y2;

		if(tempy2<oy1) return false; //si el cuerpo esta por debajo de que termina la soga
		if(tempy1>oy2) return false; //si el cuerpo esta por arriba de que empieza la soga
		
		double result1 = (ox1-x1)/(x2-x1)-(oy1-y1)/(y2-y1);
		double result2 = (ox2-x1)/(x2-x1)-(oy2-y1)/(y2-y1);
		if(!(((result1<=0)&&(result2<=0))||((result1>=0)&&(result2>=0)))) return true;

		result2 = (ox1-x1)/(x2-x1)-(oy2-y1)/(y2-y1);
		if(!(((result1<=0)&&(result2<=0))||((result1>=0)&&(result2>=0)))) return true;
		
		result2 = (ox2-x1)/(x2-x1)-(oy1-y1)/(y2-y1);
		if(!(((result1<=0)&&(result2<=0))||((result1>=0)&&(result2>=0)))) return true;
		
		return false;
}