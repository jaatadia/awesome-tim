#include "Carrito.h"
#include "Constantes.h"
#include "Cuadrado.h"
#include "CarroAtable.h"
#include "Sonidos.h"

#define TABLA 0

Carrito::Carrito(double posX, double posY, double angulo):FiguraCompuesta(ID_CARRITO,new Cuadrado(ANCHO_CARRITO,ALTO_CARRITO+RADIO_RUEDA_CARRITO+2*RADIO_PUNTA_CARRITO,posX,posY,0)){

	this->partesFigura = std::list<Figura*>();
	double posXRuedaIzq,posXRuedaDer,posYRuedaIzq,posYRuedaDer,posXCarro,posYCarro;

	calcularPosiciones(posXRuedaIzq,posXRuedaDer,posYRuedaIzq,posYRuedaDer,posXCarro,posYCarro,posX,posY);

	this->carro = new CarroAtable(posXCarro,posYCarro);
	this->ruedaIzq = new Figura(ID_RUEDA_CARRITO,new Circulo(RADIO_RUEDA_CARRITO,posXRuedaIzq,posYRuedaIzq,0));
	this->ruedaDer = new Figura(ID_RUEDA_CARRITO,new Circulo(RADIO_RUEDA_CARRITO,posXRuedaDer,posYRuedaDer,0));

	this->partesFigura.push_back(this->carro);
	this->partesFigura.push_back(this->ruedaIzq);
	this->partesFigura.push_back(this->ruedaDer);

	this->inicAngulosCentro();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		angulos.push_back((*iterFig)->getDimension()->getAngulo());
	}
	this->setAngulo(angulo);
}

Carrito::~Carrito(void){
}

void Carrito::calcularPosiciones(double& posXizq,double& posXder, double& posYizq,double& posYder, double& posX_Carro, double& posY_Carro, double posX, double posY){

	posX_Carro = posX;
//	posY_Carro = posY + ((ALTO_CARRITO+RADIO_RUEDA_CARRITO)/2)  -(RADIO_RUEDA_CARRITO + ALTO_CARRITO/2);
	posY_Carro = posY + ALTO_CARRITO/2 -(RADIO_RUEDA_CARRITO + RADIO_PUNTA_CARRITO);
	
	posXizq = ( posX_Carro - (ANCHO_CARRITO / 2) + RADIO_RUEDA_CARRITO + RADIO_RUEDA_CARRITO/2);
	posXder = ( posX_Carro + (ANCHO_CARRITO / 2) - RADIO_RUEDA_CARRITO - RADIO_RUEDA_CARRITO/2);
	posYizq = posYder = posY_Carro + (ALTO_CARRITO/2) - 0.1;

}

Figura* Carrito::clonar(){

	Cuadrado* dim = (Cuadrado*) this->getDimension();
	Figura* carrito = new Carrito(dim->getX(),dim->getY(),dim->getAngulo());
	this->completarInteraccionesPosibles(carrito);
	return carrito;
}


int Carrito::getTipoDimension(){
	return CUADRADO;
}

int Carrito::getTipoFigura(){
	return CARRITO;
}

CarroAtable* Carrito::getCarro(){
	return this->carro;
}

void Carrito::setCuerpo(b2Body* cuerpo){
	this->b2dCuerpo = cuerpo;
}

void Carrito::actualizar(){
	int VEL_MIN = 5;
	/*if((this->b2dCuerpo)->GetLinearVelocity().x > VEL_MIN){
		Sonidos::playSound(CARRITO_MUSIC);

	}*/
}

Figura* Carrito::getRuedaIzq(){
	return this->ruedaIzq;
}

Figura* Carrito::getRuedaDer(){
	return this->ruedaDer;
}

int Carrito::esAtableSoga(double x,double y){
	return this->carro->esAtableSoga(x,y);
}

void Carrito::posAtableSoga(int numero,double* x,double* y){
	this->carro->posAtableSoga(numero,x,y);
}

void Carrito::atarSoga(int numero){
	(this->carro)->atarSoga(numero);
}

void Carrito::desatarSoga(int numero){
	(this->carro)->desatarSoga(numero);
}

