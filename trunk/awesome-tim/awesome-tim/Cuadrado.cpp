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

bool Cuadrado::intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2){

	double angle = -(PI*this->getAngulo())/180.0;
	Xs1 = getX() + ((Xs1-getX()) * cos(-angle)) - ((Ys1-getY()) * sin(-angle));
	Ys1 = getY() + ((Xs1-getX()) * sin(-angle)) + ((Ys1-getY()) * cos(-angle));
	Xs2 = getX() + ((Xs2-getX()) * cos(-angle)) - ((Ys2-getY()) * sin(-angle));
	Ys2 = getY() + ((Xs2-getX()) * sin(-angle)) + ((Ys2-getY()) * cos(-angle));

	Recta* RectaExterna = new Recta(Xs1, Ys1, Xs2, Ys2);


	Segmento segPropio1(ancho/2 + getX(), -alto/2 + getY(), -ancho/2 + getX(), -alto/2 + getY());
	Segmento segPropio2(-ancho/2 + getX(), -alto/2 + getY(), -ancho/2 + getX(), alto/2 + getY());
	Segmento segPropio3(-ancho/2 + getX(), alto/2 + getY(), ancho/2 + getX(), alto/2 + getY());
	Segmento segPropio4(ancho/2 + getX(), alto/2 + getY(), ancho/2 + getX(), -alto/2 + getY());	

	if	 (segPropio1.intersecaCon(RectaExterna) || segPropio2.intersecaCon(RectaExterna) ||
		segPropio3.intersecaCon(RectaExterna) || segPropio4.intersecaCon(RectaExterna)){
		return true;
	}

	delete RectaExterna;

	return false;
}