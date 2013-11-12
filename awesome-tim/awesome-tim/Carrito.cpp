#include "Carrito.h"
#include "Constantes.h"
#include "Cuadrado.h"

#define TABLA 0

Carrito::Carrito(double posX, double posY, double angulo):FiguraCompuesta(ID_CARRITO,new Cuadrado(ANCHO_CARRITO,ALTO_CARRITO+RADIO_RUEDA_CARRITO,posX,posY,0)){

	this->partesFigura = std::list<Figura*>();
	double posXRuedaIzq,posXRuedaDer,posYRuedaIzq,posYRuedaDer,posXCarro,posYCarro;

	calcularPosiciones(posXRuedaIzq,posXRuedaDer,posYRuedaIzq,posYRuedaDer,posXCarro,posYCarro,posX,posY);

	this->carro = new Figura(ID_BASE_CARRITO,new Cuadrado(ANCHO_CARRITO,ALTO_CARRITO,posXCarro,posYCarro,0));
	this->ruedaIzq = new Figura(ID_RUEDA_CARRITO,new Circulo(RADIO_RUEDA_CARRITO,posXRuedaIzq,posYRuedaIzq,0));
	this->ruedaDer = new Figura(ID_RUEDA_CARRITO,new Circulo(RADIO_RUEDA_CARRITO,posXRuedaDer,posYRuedaDer,0));

	this->partesFigura.push_back(this->carro);
	this->partesFigura.push_back(this->ruedaIzq);
	this->partesFigura.push_back(this->ruedaDer);

	this->atado = false;

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
	posY_Carro = posY + ((ALTO_CARRITO+RADIO_RUEDA_CARRITO)/2)  -(RADIO_RUEDA_CARRITO + ALTO_CARRITO/2);

	posXizq = ( posX_Carro - (ANCHO_CARRITO / 2) + RADIO_RUEDA_CARRITO + RADIO_RUEDA_CARRITO/2);
	posXder = ( posX_Carro + (ANCHO_CARRITO / 2) - RADIO_RUEDA_CARRITO - + RADIO_RUEDA_CARRITO/2);
	posYizq = posYder = posY + ((ALTO_CARRITO+RADIO_RUEDA_CARRITO)/2)  - RADIO_RUEDA_CARRITO;

}

Figura* Carrito::clonar(){

	Cuadrado* dim = (Cuadrado*) this->getDimension();

	return new Carrito(dim->getX(),dim->getY(),dim->getAngulo());
}


int Carrito::getTipoDimension(){
	return CUADRADO;
}

int Carrito::getTipoFigura(){
	return CARRITO;
}

Figura* Carrito::getCarro(){
	return this->carro;
}

Figura* Carrito::getRuedaIzq(){
	return this->ruedaIzq;
}

Figura* Carrito::getRuedaDer(){
	return this->ruedaDer;
}

int Carrito::esAtableSoga(double x,double y){
	if (!this->atado) return 1;
	return -1;
}

void Carrito::posAtableSoga(int numero,double* x,double* y){
	if (numero == 1){
		*x = this->carro->getDimension()->getX();
		*y = this->carro->getDimension()->getY();
	}
}
void Carrito::atarSoga(int numero){
	if (numero == 1 )
		atado = true;
}
void Carrito::desatarSoga(int numero){
	if (numero == 1)
		atado = false;
}