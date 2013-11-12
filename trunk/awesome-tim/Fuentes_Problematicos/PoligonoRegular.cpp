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
	
	double X;
	double Y;

	if (this->getAnguloReal() != this->getAngulo()){	
		double angle = -(PI*this->getAngulo())/180.0;
		X = getX() + ((tX-getX()) * cos(-angle)) - ((tY-getY()) * sin(-angle));
		Y = getY() + ((tX-getX()) * sin(-angle)) + ((tY-getY()) * cos(-angle));
	}else{
		X = tX;
		Y = tY;
	}
	
	 
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


bool PoligonoRegular::intersecaCon(double XsUno, double YsUno, double XsDos, double YsDos){

	double Xs1;
	double Ys1;
	double Xs2;
	double Ys2;

	//roto al reves de como esta el poligono!
	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		Xs1 = getX() + ((XsUno-getX()) * cos(-angle)) - ((YsUno-getY()) * sin(-angle));
		Ys1 = getY() + ((XsUno-getX()) * sin(-angle)) + ((YsUno-getY()) * cos(-angle));
		Xs2 = getX() + ((XsDos-getX()) * cos(-angle)) - ((YsDos-getY()) * sin(-angle));
		Ys2 = getY() + ((XsDos-getX()) * sin(-angle)) + ((YsDos-getY()) * cos(-angle));
	}else{
		Xs1 = XsUno;
		Ys1 = YsUno;
		Xs2 = XsDos;
		Ys2 = YsDos;
	}

	Segmento* segExterno = new Segmento(Xs1, Ys1, Xs2, Ys2);

	bool interseca = false;

	int i = 0;

	double x1,y1,x2,y2;
	Segmento* segPropio;	

	//entre el primero y el ultimo
	x1 = getX() + vectorX[0];
	y1 = getY() + vectorY[0];
	x2 = getX() + vectorX[vertices-1];
	y2 = getY() + vectorY[vertices-1];

	segPropio = new Segmento(x1,y1,x2,y2);
	interseca = segPropio->intersecaCon(segExterno);

	delete segPropio;
	segPropio = NULL;

	//el resto
	while ( (i < vertices-1) && (!interseca) ){

		x1 = getX() + vectorX[i];
		y1 = getY() + vectorY[i];
		x2 = getX() + vectorX[i+1];
		y2 = getY() + vectorY[i+1];

		segPropio = new Segmento(x1,y1,x2,y2);

		interseca = segPropio->intersecaCon(segExterno);
		delete segPropio;
		segPropio = NULL;

		i++;
	}

	delete segExterno;

	return interseca;
}

Dimension* PoligonoRegular::clonar(){
	
	PoligonoRegular* polADevolver = new PoligonoRegular(getX(),getY(),radio,vertices,getAngulo());

	polADevolver->setAnguloReal( this->getAnguloReal() );

	//y todos los vertices
	for(int i=0;i<vertices;i++){
		polADevolver->setVertX( i, this->getVerticeX(i) ); 
		polADevolver->setVertY( i, this->getVerticeY(i) ) ;
	}

	return (Dimension*) polADevolver;
}


bool PoligonoRegular::choqueConDimension(Dimension* dim){

	Dimension* dimAChocar;

	//rota al reves mio  la que me pasaron, solo si no estoy rotado de verdad
	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		dimAChocar = dim->rotarDimension(getX(),getY(),- this->getAngulo());
	}else{
		dimAChocar = dim->clonar();
	}

	//me fijo si alguna de sus aristas corta la otra dimension
	bool interseca = false;

	int i = 0;

	double x1,y1,x2,y2;

	//entre el primero y el ultimo
	x1 = this->getX() + vectorX[0];
	y1 = getY() + vectorY[0];
	x2 = getX() + vectorX[vertices-1];
	y2 = getY() + vectorY[vertices-1];

	interseca = dimAChocar->intersecaCon( x1, y1, x2, y2);

	//el resto
	while ( (i < vertices-1) && (!interseca) ){

		x1 = getX() + vectorX[i];
		y1 = getY() + vectorY[i];
		x2 = getX() + vectorX[i+1];
		y2 = getY() + vectorY[i+1];

		interseca = dimAChocar->intersecaCon( x1, y1, x2, y2);

		i++;
	}

	delete dimAChocar;

	return interseca;

}

Dimension* PoligonoRegular::rotarDimension(double xRot, double yRot, double angulo){

	double angle = (PI*angulo)/180.0;

	PoligonoRegular* polADevolver = (PoligonoRegular*)this->clonar();
//roto la posicion y cada vertice
	polADevolver->setX( xRot + ((this->getX()-xRot) * cos(-angle)) - ((this->getY()-yRot) * sin(-angle)) );
	polADevolver->setY( yRot + ((this->getX()-xRot) * sin(-angle)) + ((this->getY()-yRot) * cos(-angle)) );

	for(int i=0; i<vertices; i++){
		polADevolver->setVertX ( i , 0 + ((vectorX[i]-0) * cos(-angle)) - ((vectorY[i]-0) * sin(-angle)) );
		polADevolver->setVertY ( i , 0 + ((vectorX[i]-0) * sin(-angle)) + ((vectorY[i]-0) * cos(-angle)) );
	}
//tengo que hacer esto porque pueden estar desfasdos (antes de la primera rotacion)	
	polADevolver->setAngulo( polADevolver->getAnguloReal() );

	polADevolver->setAngulo( polADevolver->getAngulo() + angulo );
	polADevolver->setAnguloReal( polADevolver->getAnguloReal() + angulo );

	return polADevolver;
}

void PoligonoRegular::setVertX(int i, double x){
	this->vectorX[i] = x;
}


void PoligonoRegular::setVertY(int i, double y){
	this->vectorY[i] = y;
}

double PoligonoRegular::getVerticeX(int i){

	return this->vectorX[i];
}

double PoligonoRegular::getVerticeY(int i){

	return this->vectorY[i];
}