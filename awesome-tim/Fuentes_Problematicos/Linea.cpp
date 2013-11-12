#include "Linea.h"
#include "Cuadrado.h"

Linea::Linea(double x1,double y1,double x2, double y2,double ancho):Figura(ID_CORREA,new DLinea(x1,y1,x2,y2,ancho),true)
{
	this->setCambio(true);
	puesto = false;
	simple = false;
}

Linea::Linea(const char* ID,bool simple,double x1,double y1,double x2, double y2,double ancho):Figura(ID,new DLinea(x1,y1,x2,y2,ancho),true)
{
	this->setCambio(true);
	puesto = false;
	this->simple = simple;
}

Linea::~Linea(void)
{
}

void Linea::setPunto1(double x1,double y1){
	dimension->putP1(x1,y1);
	puesto = true;
	
	delete this->myVista;
	this->myVista = new VistaLinea(this,simple);
}

void Linea::setPunto2(double x2,double y2){
	dimension->putP2(x2,y2);
}

void Linea::getPunto1(double* x1,double* y1){
	*x1 = ((DLinea*)dimension)->x1;
	*y1 = ((DLinea*)dimension)->y1;
}

void Linea::getPunto2(double* x2,double* y2){
	*x2 = ((DLinea*)dimension)->x2;
	*y2 = ((DLinea*)dimension)->y2;
}

void Linea::setFigura1(Figura* fig){
	fig1 = fig;
	puesto = true;

	delete this->myVista;
	this->myVista = new VistaLinea(this,simple);
}

Figura* Linea::clonar(){
	//return new Linea(ID_CORREA,(DLinea *)getDimension()->clonar());
	return new Linea(ID_CORREA,new DLinea(((DLinea*)dimension)->x1,((DLinea*)dimension)->y1,((DLinea*)dimension)->x2,((DLinea*)dimension)->y2,((DLinea*)dimension)->ancho));
}

Linea::Linea(const char* ID,DLinea* dim):Figura(ID,dim,true)
{
	fig1=fig2=NULL;
	this->setCambio(true);
	puesto = false;
	simple = false;
}

bool Linea::choqueConFigura(Figura* fig){

	return false;
}

bool Linea::choqueConDimension(Dimension* dim){

	return false;
}

void Linea::dibujar(Superficie* super){
	myVista->dibujar(super);
	myVista->dibujar(super);
	myVista->dibujar(super);
}

void Linea::actualizar(){
	if(getFigura1()!=NULL){
		double x,y;
		this->posFigura1(&x,&y);
		this->setPunto1(x,y);
	}
	if(getFigura2()!=NULL){
		double x,y;
		this->posFigura2(&x,&y);
		this->setPunto2(x,y);
	}
}