#include "Triangulo.h"

Triangulo::Triangulo(double X, double Y, double angulo, Posicion* punto1, Posicion* punto2, Posicion* punto3): Dimension(X,Y,angulo){
	this->A1 = punto1;
	this->A2 = punto2;
	this->A3 = punto3;
	this->centroX = X;
	this->centroY = Y;
	this->angulo = angulo;
}


Triangulo::~Triangulo(void){

	delete(this->A1);
	delete(this->A2);
	delete(this->A3);

}

bool Triangulo::todos_positivos(double num1, double num2, double num3, double num4){
	return ((num1>0) && (num2>0) && (num3>0) && (num4>0));
}

bool Triangulo::todos_negativos(double num1, double num2, double num3, double num4){
	return ((num1<=0) && (num2<=0) && (num3<=0) && (num4<=0));
}

bool Triangulo::orientaciones_iguales(double Origen,double circ1,double circ2,double circ3){
	return (todos_positivos(Origen,circ1,circ2,circ3) || todos_negativos(Origen,circ1,circ2,circ3));
}

bool Triangulo::puntoPertenece(double x, double y){
//A partir de esta direccion, encontre como saber si un punto pertenece o no a un triangulo: "http://www.dma.fi.upm.es/mabellanas/tfcs/kirkpatrick/Aplicacion/algoritmos.htm"

	Posicion* puntoP = new Posicion(x,y);
	if(!puntoP) return false;

	double circulacionOrigen = sentido_circulacion(this->A1,this->A2,this->A3);
	double circulacion1 = sentido_circulacion(this->A1, this->A2, puntoP);
	double circulacion2 = sentido_circulacion(this->A2, this->A3, puntoP);
	double circulacion3 = sentido_circulacion(this->A3, this->A1, puntoP);

	delete(puntoP);

	return orientaciones_iguales(circulacionOrigen,circulacion1,circulacion2,circulacion3);
}

double Triangulo::sentido_circulacion(Posicion* A1,Posicion* A2,Posicion* A3){

	double A1x, A1y, A2x, A2y, A3x, A3y;
	
	A1x = A1->getX();
	A2x = A2->getX();
	A3x = A3->getX();

	A1y = A1->getY();
	A2y = A2->getY();
	A3y = A3->getY();

	return ((A1x - A3x) * (A2y - A3y) - (A1y - A3y) * (A2x - A3x)); 

}