#include "Figura.h"
#include "Recta.h"
#include "Constantes.h"
#include <math.h>

Figura::Figura(const char* ID,Dimension* dim,bool crearVista){
	this->ID = ID;
	this->dimension = dim;
	this->setCambio(true);
	if (crearVista){
		this->myVista = new VistaFigura(this);
	}else{
		this->myVista = NULL;
	}
	this->traslucido = false;
	this->cuerpo = NULL;
}


Figura::~Figura(void){
	
	/*if(correa){
		if ((correa->getFigura1()==this)&&(correa->getFigura2()!=NULL)){
			correa->getFigura2()->setCorrea(NULL);
		}else if ((correa->getFigura2()==this)&&(correa->getFigura1()!=NULL)){
			correa->getFigura1()->setCorrea(NULL);
		}
	}*/
	if (myVista != NULL)
		delete myVista;
	if (dimension != NULL)
		delete dimension;
}

void Figura::cambiarPosicion(double x,double y)
{
	dimension->setX( dimension->getX() + x);
	dimension->setY( dimension->getY() + y);
}

bool Figura::esMiPosicion(double x,double y)
{

	double miX = x;
	double miY = y;

	//comentar esto para que ande como antes (acordarse de cambiar tambien VistaFigura.cpp redraw)
/*
	//dado que las escalas pueden ser incorrectas si se rot� la figura, se rota el punto segun los pixels
	double miAngulo = (dimension->getAngulo())*PI/180;
	double centroXReal = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(this->dimension->getX())+0.0;
	double centroYReal = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(this->dimension->getY())+0.0;
	double xReal = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(x)+0.0;
	double yReal = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(y)+0.0;
	
	double tempX = centroXReal + (xReal - centroXReal)*cos(miAngulo) - (yReal - centroYReal)*sin(miAngulo);
	double tempY = centroYReal + (xReal - centroXReal)*sin(miAngulo) + (yReal - centroYReal)*cos(miAngulo);

	//una vez rotado las escalas ya son correctas
	tempX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(tempX);
	tempY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(tempY);
	
	//pero como el punto fue rotado, lo rotamos al reves para que sea la misma posicion de antes
	miAngulo*=-1;
	double cX = dimension->getX();
	double cY = dimension->getY();

	miX = cX + (tempX - cX)*cos(miAngulo) - (tempY - cY)*sin(miAngulo);
	miY = cY + (tempX - cX)*sin(miAngulo) + (tempY - cY)*cos(miAngulo);
	//terminar de comentar aca
*/
	return dimension->puntoPertenece( miX, miY);
}

void Figura::dibujarEnPixel(Superficie* super){
	myVista->dibujarEnPixel(super);
	setCambio(false);
}

void Figura::dibujar(Superficie* super){
	myVista->dibujar(super);
	setCambio(false);
}

void Figura::dibujar(Superficie* super,int xIni, int yIni){
	myVista->dibujar(super,xIni,yIni);
	setCambio(false);
}

const char* Figura::getID(){
	return (this->ID.c_str());
};
Dimension* Figura::getDimension(){
	return (this->dimension);
};

bool Figura::intersecaCon(double X1, double Y1, double X2, double Y2){
	return dimension->intersecaCon( X1, Y1, X2, Y2);
}

Figura* Figura::clonar(){
	return new Figura(ID.c_str(),dimension->clonar());
}

void Figura::setTraslucido(bool flag){
	this->traslucido=flag;
	setCambio(true);
}

void Figura::setAngulo(double angulo){ 
	
	double margen = 2;
	if(
		(dimension->getAngulo()<(angulo-margen))||
		(dimension->getAngulo()>(angulo+margen))
	){
		dimension->setAngulo(angulo); 
		setCambio(true);
	}
}

double Figura::getLargo(){
	return 1;
}