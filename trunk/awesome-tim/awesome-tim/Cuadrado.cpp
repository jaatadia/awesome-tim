#include "Cuadrado.h"


Cuadrado::Cuadrado(double ancho,double alto,double X, double Y, double angulo): Dimension(X,Y,angulo) {
	this->ancho = ancho;
	this->alto = alto;

	vertice1.setX(ancho/2);
	vertice1.setY(-alto/2);

	vertice2.setX(-ancho/2);
	vertice2.setY(-alto/2);

	vertice3.setX(-ancho/2);
	vertice3.setY(alto/2);

	vertice4.setX(ancho/2);
	vertice4.setY(alto/2);
}

Cuadrado::~Cuadrado(void){
}

double Cuadrado::getAncho(){
	return ancho;
}

double Cuadrado::getAlto(){
	return alto;
}

bool Cuadrado::puntoPertenece(double XPunto, double YPunto){

	bool pertenece = true;

	Recta r1(vertice1.getX(), vertice1.getY(), vertice2.getX(), vertice2.getY());
	Recta r2(vertice2.getX(), vertice2.getY(), vertice3.getX(), vertice3.getY());
	Recta r3(vertice3.getX(), vertice3.getY(), vertice4.getX(), vertice4.getY());
	Recta r4(vertice4.getX(), vertice4.getY(), vertice1.getX(), vertice1.getY());

	//roto el punto al reves de como esta el cuadrado

	double angle = -(PI*this->getAngulo())/180.0;
	double Xrotado = getX() + ((XPunto-getX()) * cos(-angle)) - ((YPunto-getY()) * sin(-angle));
	double Yrotado = getY() + ((XPunto-getX()) * sin(-angle)) + ((YPunto-getY()) * cos(-angle));

	double XrelCentro =  Xrotado - this->getX();
	double YrelCentro =  Yrotado - this->getY();
	//verifico lado por lado

	if (r4.puntoADerecha(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	if (r2.puntoAIzquierda(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	if (r1.puntoPorArriba(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	if (r3.puntoPorDebajo(XrelCentro,YrelCentro)){
		pertenece = false;
	}
	
	return pertenece;
}


Dimension* Cuadrado::clonar(){
	return new Cuadrado(ancho,alto,getX(),getY(),angulo);
}

bool Cuadrado::intersecaCon(double XsUno, double YsUno, double XsDos, double YsDos){

	double angle = -(PI*this->getAngulo())/180.0;
	double Xs1 = getX() + ((XsUno-getX()) * cos(-angle)) - ((YsUno-getY()) * sin(-angle));
	double Ys1 = getY() + ((XsUno-getX()) * sin(-angle)) + ((YsUno-getY()) * cos(-angle));
	double Xs2 = getX() + ((XsDos-getX()) * cos(-angle)) - ((YsDos-getY()) * sin(-angle));
	double Ys2 = getY() + ((XsDos-getX()) * sin(-angle)) + ((YsDos-getY()) * cos(-angle));

	Segmento* segExterno = new Segmento(Xs1, Ys1, Xs2, Ys2);


	Segmento segPropio1(ancho/2 + getX(), -alto/2 + getY(), -ancho/2 + getX(), -alto/2 + getY());
	Segmento segPropio2(-ancho/2 + getX(), -alto/2 + getY(), -ancho/2 + getX(), alto/2 + getY());
	Segmento segPropio3(-ancho/2 + getX(), alto/2 + getY(), ancho/2 + getX(), alto/2 + getY());
	Segmento segPropio4(ancho/2 + getX(), alto/2 + getY(), ancho/2 + getX(), -alto/2 + getY());	

	if	 (segPropio1.intersecaCon(segExterno) || segPropio2.intersecaCon(segExterno) ||
		segPropio3.intersecaCon(segExterno) || segPropio4.intersecaCon(segExterno)){
		return true;
	}

	delete segExterno;

	return false;
}


void Cuadrado::setAncho(double nuevoLargo){
	this->ancho = nuevoLargo;

	vertice1.setX(ancho/2);
	vertice1.setY(-alto/2);

	vertice2.setX(-ancho/2);
	vertice2.setY(-alto/2);

	vertice3.setX(-ancho/2);
	vertice3.setY(alto/2);

	vertice4.setX(ancho/2);
	vertice4.setY(alto/2);
}


bool Cuadrado::choqueConDimension(Dimension* dim){

	//me fijo si alguna de sus aristas corta la otra dimension
	bool interseca = false;

	if( dim->intersecaCon(vertice1.getX() + getX(),vertice1.getY() + getY(),vertice2.getX() + getX(),vertice2.getY() + getY()) ||
		dim->intersecaCon(vertice2.getX() + getX(),vertice2.getY() + getY(),vertice3.getX() + getX(),vertice3.getY() + getY()) ||
		dim->intersecaCon(vertice3.getX() + getX(),vertice3.getY() + getY(),vertice4.getX() + getX(),vertice4.getY() + getY()) ||
		dim->intersecaCon(vertice4.getX() + getX(),vertice4.getY() + getY(),vertice1.getX() + getX(),vertice1.getY() + getY()) ){
		interseca = true;
	}
	
	return interseca;

}