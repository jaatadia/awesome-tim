#include "Balancin.h"
#include "Constantes.h"
#include "Cuadrado.h"

#define TABLA 0
#define PUNTA1 1
#define PUNTA2 2
#define BASE 3

Balancin::Balancin(Figura** figuras):Figura("",new Cuadrado(ANCHO_DEFAULT,ALTO_DEFAULT,POSX_DEFAULT,POSY_DEFAULT, ANGULO_DEFAULT)){
	this->tabla = figuras[TABLA];
	this->punta1 = figuras[PUNTA1];
	this->punta2 = figuras[PUNTA2];
	this->base = figuras[BASE];

	this->listaID[TABLA] = this->tabla->getID();
	this->listaID[PUNTA1] = this->punta1->getID();
	this->listaID[PUNTA2] = this->punta2->getID();
	this->listaID[BASE] = this->base->getID();

	this->posX = (tabla->getDimension())->getX();
	this->posY = (tabla->getDimension())->getY();

	this->myVista = new VistaFigura(this);
}

void Balancin::cambiarPosicion(double x,double y){
	tabla->cambiarPosicion(x,y);
	punta1->cambiarPosicion(x,y);
	punta2->cambiarPosicion(x,y);
	base->cambiarPosicion(x,y);
}

bool Balancin::esMiPosicion(double x,double y){

	bool perTabla = tabla->esMiPosicion(x,y);
	bool perPunta1 = punta1->esMiPosicion(x,y);
	bool perPunta2 = punta2->esMiPosicion(x,y);
	bool perBase = base->esMiPosicion(x,y);

	return (perTabla || perPunta1 || perPunta2 || perBase);
}

void Balancin::dibujar(Superficie* super){

	tabla->dibujar(super);
	punta1->dibujar(super);
	punta2->dibujar(super);
	base->dibujar(super);
	setCambio(false);
}

const char** Balancin::getListaDeIDs(){
	return (this->listaID);
}

bool Balancin::intersecaCon(double X1, double Y1, double X2, double Y2){
	//FIXME: No se que tiene que hacer
	bool interTabla = tabla->intersecaCon(X1,Y1,X2,Y2);
	bool interPunta1 = punta1->intersecaCon(X1,Y1,X2,Y2);
	bool interPunta2 = punta2->intersecaCon(X1,Y1,X2,Y2);
	bool interBase = base->intersecaCon(X1,Y1,X2,Y2);

	return (interTabla || interPunta1 || interPunta2 || interBase);
}

Figura* Balancin::clonar(){
	Figura* figuras[CANT_ELEM_BALANCIN];
	figuras[TABLA] = tabla->clonar();
	figuras[PUNTA1] = punta1->clonar();
	figuras[PUNTA2] = punta2->clonar();
	figuras[BASE] = base->clonar();
	return new Balancin(figuras);
}

void Balancin::setTraslucido(bool flag){
	(this->tabla)->setTraslucido(flag);
	(this->punta1)->setTraslucido(flag);
	(this->punta2)->setTraslucido(flag);
	(this->base)->setTraslucido(flag);
	setCambio(true);
}

void Balancin::setAngulo(double angulo){ 
	//FIXME
	//setea el angulo de la tabla
	tabla->setAngulo(angulo);

	//Seteamos el angulo de la base solo si ambas pueden girar
}

Balancin::~Balancin(void){
	delete tabla;
	delete punta1;
	delete punta2;
	delete base;
	delete myVista;
}
