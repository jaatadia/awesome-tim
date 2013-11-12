#include "PedacitoSoga.h"

PedacitoSoga::PedacitoSoga(double centroX,double centroY,double largo,double angulo):Figura(ID_SOGA,new Cuadrado(0,0,0,0,0),false){
	this->myVista = new VistaPedacitoSoga(this);
	this->centroX = centroX;
	this->centroY = centroY;
	this->longitud = largo;
	//this->setAngulo(angulo);
}

void PedacitoSoga::setX(double x){
	this->centroX = x;
	dimension->setX(x);
}

void PedacitoSoga::setY(double y){
	this->centroY = y;
	dimension->setY(y);
}

void PedacitoSoga::setAngulo(double angulo){
	px1 = centroX-longitud/2.0;
	py1 = centroY-longitud/2.0;
	px2 = centroX+longitud/2.0;
	py2 = centroY+longitud/2.0;

	//double x1 = centroX-longitud/2.0;
	//double y1 = centroY;
	//double x2 = centroX+longitud/2.0;
	//double y2 = centroY;
	//
	//double ang = -angulo*PI/180;

	//px1 = centroX + (x1-centroX)*cos(ang) - (y1-centroY)*sin(ang);
	//py1 = centroY + (x1-centroX)*sin(ang) + (y1-centroY)*cos(ang);

	//px2 = centroX + (x2-centroX)*cos(ang) - (y2-centroY)*sin(ang);
	//py2 = centroY + (x2-centroX)*sin(ang) + (y2-centroY)*cos(ang);

}