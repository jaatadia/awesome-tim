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
	return ((DLinea*)dim)->meChoca(dim);
}