#include "Triangulo2.h"
#include <cmath>
#include "Constantes.h"

Triangulo2::Triangulo2(double X, double Y, double angulo, double base,double altura): Dimension(X,Y,angulo){
	this->base = base;
	this->altura = altura;

	double extra = 0;

	x1 = 0;
	y1 = -(altura/2);

	x2 = -(base/2);
	y2 = (altura/2);

	x3 = +base/2;
	y3 = (altura/2);

}

Triangulo2::~Triangulo2(void)
{
}

bool Triangulo2::puntoPertenece(double tX, double tY){
	
	double angle = -(PI*this->getAngulo())/180.0;
	double tx1 = getX() + x1;//((x1) * cos(angle)) - ((y1) * sin(angle));
	double ty1 = getY() + y1;//((x1) * sin(angle)) + ((y1) * cos(angle));
	double tx2 = getX() + x2;//((x2) * cos(angle)) - ((y2) * sin(angle));
	double ty2 = getY() + y2;//((x2) * sin(angle)) + ((y2) * cos(angle));
	double tx3 = getX() + x3;//((x3) * cos(angle)) - ((y3) * sin(angle));
	double ty3 = getY() + y3;//((x3) * sin(angle)) + ((y3) * cos(angle));


	double X = getX() + ((tX-getX()) * cos(-angle)) - ((tY-getY()) * sin(-angle));
	double Y = getY() + ((tX-getX()) * sin(-angle)) + ((tY-getY()) * cos(-angle));

	bool signoOK = true;
	double signo;
	double signoClick;

	signo = enRecta(getX(),getY(),tx1,ty1,tx2,ty2);
	signoClick = enRecta(X,Y,tx1,ty1,+tx2,+ty2);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	if(!signoOK) return false;

	signo = enRecta(getX(),getY(),tx1,ty1,tx3,ty3);
	signoClick = enRecta(X,Y,tx1,ty1,+tx3,+ty3);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	if(!signoOK) return false;

	signo = enRecta(getX(),getY(),tx2,ty2,tx3,ty3);
	signoClick = enRecta(X,Y,tx2,ty2,+tx3,+ty3);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	
	return signoOK;
}

double Triangulo2::getAncho(void){
	return base;
}

double Triangulo2::getAlto(void){
	return altura;
}

double Triangulo2::enRecta(double x,double y,double x0,double y0,double x1,double y1){
	//return (((x-x0)/(x1-x0))-((y-y0)/(y1-y0)));
	return (((x-x0)*(y1-y0))-((y-y0)*(x1-x0)));
}

Dimension* Triangulo2::clonar(){
	return new Triangulo2(getX(),getY(),getAngulo(),base,altura);
}