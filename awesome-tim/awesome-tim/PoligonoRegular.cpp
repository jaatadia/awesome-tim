#include "PoligonoRegular.h"
#include "Constantes.h"
#include <cmath>
#include <stdlib.h>

PoligonoRegular::PoligonoRegular(double x, double y,double radio,int vert,double angulo):Dimension(x,y,angulo)
{
	if (vert<=2) vertices = 3;
	else if(vert>100) vertices = 100;
	else vertices = vert;

	this->radio = radio;
	
	
	double ang = PI/2;
	double aumento = 2*PI/vertices;

	for(int i=0;i<vertices;i++){
		vectorX[i] = radio*cos(ang);
		vectorY[i] = -(radio*sin(ang));
		ang+=aumento;
	}
}

PoligonoRegular::~PoligonoRegular(void)
{
}

bool PoligonoRegular::puntoPertenece(double tX, double tY){
	
	double angle = -(PI*this->getAngulo())/180.0;
	double X = getX() + ((tX-getX()) * cos(-angle)) - ((tY-getY()) * sin(-angle));
	double Y = getY() + ((tX-getX()) * sin(-angle)) + ((tY-getY()) * cos(-angle));

	
	 
	bool signoOK = true;
	double signo;
	double signoClick;
	double x1,x2,y1,y2;
	

	//entre el primero y el ultimo
	x1 = getX() + vectorX[0];
	y1 = getY() + vectorY[0];
	x2 = getX() + vectorX[vertices-1];
	y2 = getY() + vectorY[vertices-1];

	signo = enRecta(getX(),getY(),x1,y1,x2,y2);
	signoClick = enRecta(X,Y,x1,y1,x2,y2);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);

	//el resto
	int i = 0;
	while((i<(vertices-1))&&(signoOK)){
		
		x1 = getX()+vectorX[i];
		y1 = getY()+vectorY[i];
		x2 = getX()+vectorX[i+1];
		y2 = getY()+vectorY[i+1];

		signo = enRecta(getX(),getY(),x1,y1,x2,y2);
		signoClick = enRecta(X,Y,x1,y1,x2,y2);
		if(signoClick<0) signoOK = (signo<0);
		else if(signoClick>0) signoOK = (signo>0);
		
		i++;
	}
	
	return signoOK;
}

double PoligonoRegular::getAncho(void){
	return 2*radio;
}
double PoligonoRegular::getAlto(void){
	return getAncho();
}

double PoligonoRegular::enRecta(double x,double y,double x0,double y0,double x1,double y1){
	return (((x-x0)*(y1-y0))-((y-y0)*(x1-x0)));
};
double PoligonoRegular::getRadio(){
	return this->radio;
};
double PoligonoRegular::getCantVertices(){
	return this->vertices;
};