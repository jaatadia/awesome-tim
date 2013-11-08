#include "Figura.h"
#include "Recta.h"
#include "Constantes.h"
#include <math.h>

Figura::Figura(const char* ID,Dimension* dim,bool crearVista){
	marcada = false;
	this->ID = ID;
	this->dimension = dim;
	this->setCambio(true);
	if (crearVista){
		this->myVista = new VistaFigura(this);
	}else{
		this->myVista = NULL;
	}
	this->traslucido = false;
	this->superpuesta = false;
	fig1 = fig2 = NULL;

	this->es_fija = false;
	this->interactua_en_play = false;
}


Figura::~Figura(void){
	
	if (myVista != NULL)
		delete myVista;
	if (dimension != NULL)
		delete dimension;
}

bool Figura::esFija(){
	return this->es_fija;
}

void Figura::fijarFigura(){
	this->es_fija = true;
}

bool Figura::esInteractuableEnPlay(){
	return this->interactua_en_play;
}

void Figura::hacerInteractuableEnPlay(){
	this->interactua_en_play = true;
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
	//dado que las escalas pueden ser incorrectas si se rotó la figura, se rota el punto segun los pixels
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

Figura* Figura::clonar(bool flag){
	return this->clonar();
}

Figura* Figura::clonar(){
	return new Figura(ID.c_str(),dimension->clonar());
}

void Figura::setTraslucido(bool flag){
	if(this->traslucido != flag){
		this->traslucido=flag;
		setCambio(true);
	}
}

void Figura::setSuperpuesta(bool flag){
	if(this->superpuesta != flag){
		this->superpuesta = flag;
		setCambio(true);
	}
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

void Figura::setX( double x ){
	dimension->setX(x);
}

void Figura::setY( double y ){
	dimension->setY(y);
}

bool Figura::choqueConFigura(Figura* fig){

	//me fijo si fig que me pasaron choca con esta dimension (para cada una que tenga en este caso solo 1)
	bool choca = false;

	Dimension* dimensionRotada = dimension->rotarDimension(dimension->getX(),dimension->getY(),dimension->getAngulo());

	choca = fig->choqueConDimension(dimensionRotada);
	//caso en que una esta dentro de la otra
	if ( (!choca) && fig->esMiPosicion(this->getDimension()->getX() , this->getDimension()->getY()) ){
		choca = true;
	}

	delete dimensionRotada;

	return choca;
}

//de nuevo deberia ser contra todas las dimensiones si es compuesta
// pero aca solo tengo una
bool Figura::choqueConDimension(Dimension* dim){
//como no lo se en la figura delego a la dimension (o dimensiones).
	return dimension->choqueConDimension(dim);
}
