#include "Linea.h"
#include "Cuadrado.h"

Linea::Linea(double x1,double y1,double x2, double y2,double ancho):Figura(ID_CORREA,new DLinea(x1,y1,x2,y2,ancho),true)
{
	fig1=fig2=NULL;
	this->setCambio(true);
	puesto = false;
}

Linea::~Linea(void)
{
}

void Linea::setPunto1(double x1,double y1){
	((DLinea *)this->getDimension())->putP1(x1,y1);
	puesto = true;
	
	delete this->myVista;
	this->myVista = new VistaLinea(this);
}

void Linea::setPunto2(double x2,double y2){
	((DLinea *)this->getDimension())->putP2(x2,y2);
}

void Linea::setPunto1(Figura* fig){
	fig1 = fig;
	puesto = true;

	delete this->myVista;
	this->myVista = new VistaLinea(this);
}
	
void Linea::setPunto2(Figura* fig){
	fig2 = fig;
}

Figura* Linea::clonar(){
	return new Linea((DLinea *)getDimension()->clonar());
}

Linea::Linea(DLinea* dim):Figura(ID_CORREA,dim,true)
{
	fig1=fig2=NULL;
	this->setCambio(true);
	puesto = false;
}
