#include "Triangulo.h"

Triangulo::Triangulo(double X, double Y, double angulo, double base, double altura): Dimension(X,Y,angulo){
	this->centroX = X;
	this->centroY = Y;
	this->angulo = angulo;
	this->base = base;
	this->altura = altura;
	calcular_puntos();
}

void Triangulo::calcular_puntos(void){
	//FIXME: No calcula los puntos si hay angulo distinto de 0

	double A1x, A1y, A2x, A2y, A3x, A3y;

	A1x = this->centroX + (this->base / 2.0);
	A1y = this->centroY - (this->altura / 2.0);

	A2x = this->centroX - (this->base / 2.0);
	A2y = this->centroY - (this->altura / 2.0);

	A3x = this->centroX;
	A3y = this->centroY + (this->altura / 2.0);

	this->A1 = new Posicion(A1x,A1y);
	this->A2 = new Posicion(A2x,A2y);
	this->A3 = new Posicion(A3x,A3y);
}

//No utilizar este constructr salvo para pruebas (no necesariamente el centro es real ya que no lo verifica)
Triangulo::Triangulo(double X, double Y, double angulo, Posicion* punto1,Posicion* punto2,Posicion* punto3): Dimension(X,Y,angulo){
	this->A1 = punto1;
	this->A2 = punto2;
	this->A3 = punto3;
	this->centroX = X; //No lo verifica
	this->centroY = Y; //No lo verifica
	this->angulo = angulo; //No lo verifica
	this->base = 0; //Para que no de error al pedir un get
	this->altura = 0; //Para que no de error al pedir un get
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

// Un punto pertenece al triangulo solo si esta en el interior de el. Si pertenece a su perimetro,
// entonces no pertenece al triangulo :P
bool Triangulo::puntoPertenece(double x, double y){
//A partir de esta direccion, encontre como saber si un punto pertenece o no a un triangulo: "http://www.dma.fi.upm.es/mabellanas/tfcs/kirkpatrick/Aplicacion/algoritmos.htm"

	Posicion* puntoP = new Posicion(x,y);
	if(!puntoP) return false;

	double A1A2A3 = sentido_circulacion(this->A1,this->A2,this->A3);
	double A1A2P = sentido_circulacion(this->A1, this->A2, puntoP);
	double A2A3P = sentido_circulacion(this->A2, this->A3, puntoP);
	double A3A1P = sentido_circulacion(this->A3, this->A1, puntoP);

	delete(puntoP);

	return orientaciones_iguales(A1A2A3,A1A2P,A2A3P,A3A1P);
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

double Triangulo::getAncho(void){
	return this->base;
}

double Triangulo::getAlto(void){
	return this->altura;
}


double Triangulo::getAngulo(void){
	return this->angulo;
}

void Triangulo::setAngulo(double ang){
	this->angulo = ang;
	calcular_puntos();
}
