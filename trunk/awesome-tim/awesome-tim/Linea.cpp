#include "Linea.h"
#include "Cuadrado.h"

Linea::Linea(double x1,double y1,double x2, double y2,double ancho):Figura(ID_CORREA,new Cuadrado((x2-x1)/2,(y2-y1)/2,x1,x2,0),true)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->ancho = ancho;
	
	//this->myVista = new VistaLinea();
}

Linea::~Linea(void)
{
}

void Linea::setPunto1(double x1,double y1){
	this->x1 = x1;
	this->y1 = y1;
}

void Linea::setPunto2(double x2,double y2){
	this->x2 = x2;
	this->y2 = y2;
}

Figura* Linea::clonar(){
	return new Linea(x1,y1,x2,y2,ancho);
}