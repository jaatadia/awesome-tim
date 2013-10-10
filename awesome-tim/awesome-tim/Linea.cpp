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

void Linea::setFigura1(Figura* fig){
	fig1 = fig;
	puesto = true;

	delete this->myVista;
	this->myVista = new VistaLinea(this,simple);
}

Figura* Linea::clonar(){
	return new Linea(ID_CORREA,(DLinea *)getDimension()->clonar());
}

Linea::Linea(const char* ID,DLinea* dim):Figura(ID,dim,true)
{
	fig1=fig2=NULL;
	this->setCambio(true);
	puesto = false;
	simple = false;
}
