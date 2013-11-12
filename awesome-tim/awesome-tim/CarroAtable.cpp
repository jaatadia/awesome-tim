#include "CarroAtable.h"
#include "Constantes.h"
#include "Cuadrado.h"

CarroAtable::CarroAtable(double posX, double posY):FiguraCompuesta(ID_BASE_CARRITO,new Cuadrado(ANCHO_CARRITO+4*RADIO_PUNTA_CARRITO,ALTO_CARRITO,posX,posY,0)){

	double angulo = 0;

	this->partesFigura = std::list<Figura*>();
	double posXPuntaIzq,posXPuntaDer,posYPuntaIzq,posYPuntaDer;

	calcularPosPuntas(posXPuntaIzq,posXPuntaDer,posYPuntaIzq,posYPuntaDer,posX,posY,angulo, 162.89727103 , 17.10272897);

	this->tabla = new Figura(ID_BASE_CARRITO,new Cuadrado(ANCHO_CARRITO,ALTO_CARRITO,posX,posY,0));
	this->circIzq = new Figura(ID_PUNTA_CARRITO,new Circulo(RADIO_PUNTA_CARRITO,posXPuntaIzq,posYPuntaIzq,0));
	this->circDer = new Figura(ID_PUNTA_CARRITO,new Circulo(RADIO_PUNTA_CARRITO,posXPuntaDer,posYPuntaDer,0));

	this->partesFigura.push_back(this->tabla); //tabla
	this->partesFigura.push_back(this->circIzq); //punta izq
	this->partesFigura.push_back(this->circDer); //punta der

	this->atadoDerecha = false;
	this->atadoIzquierda = false;

	this->inicAngulosCentro();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		//y obviamente aca poner en quien herede los que correspondan
		angulos.push_back((*iterFig)->getDimension()->getAngulo());
	}
	this->setAngulo(angulo);
}

CarroAtable::~CarroAtable(void){}

void CarroAtable::calcularPosPuntas(double& posXizq,double& posXder, double& posYizq,double& posYder, double posX_Tabla, double posY_Tabla, double angulo, double angulo1, double angulo2){

	posXizq = ( posX_Tabla - (ANCHO_CARRITO / 2) + RADIO_PUNTA_CARRITO);
	posXder = ( posX_Tabla + (ANCHO_CARRITO / 2) - RADIO_PUNTA_CARRITO);
	posYizq = posYder = ( posY_Tabla - (ALTO_CARRITO / 2) - (0.5)*RADIO_PUNTA_CARRITO);
}

Figura* CarroAtable::clonar(){

	Cuadrado* dim = (Cuadrado*) this->getDimension();

	return new CarroAtable(dim->getX(),dim->getY());
}


int CarroAtable::getTipoDimension(){
	return CUADRADO;
}

int CarroAtable::getTipoFigura(){
	return CARRO_ATABLE;
}

Figura* CarroAtable::getTabla(){
	return this->tabla;
}

Figura* CarroAtable::getPuntaIzq(){
	return this->circIzq;
}

Figura* CarroAtable::getPuntaDer(){
	return this->circDer;
}

int CarroAtable::esAtableSoga(double x,double y){
	if ((!this->atadoIzquierda) && x <= this->getDimension()->getX()) return 1;
	else if ((!this->atadoDerecha) && x > this->getDimension()->getX()) return 2;
	return -1;
}

void CarroAtable::posAtableSoga(int numero,double* x,double* y){
	if (numero == 1){
		*x = this->circIzq->getDimension()->getX();
		*y = this->circIzq->getDimension()->getY();
	}else if (numero == 2){
		*x = this->circDer->getDimension()->getX();
		*y = this->circDer->getDimension()->getY();
	}
}

void CarroAtable::atarSoga(int numero){
	if (numero == 1){
		atadoIzquierda = true;
	}else if (numero == 2){
		atadoDerecha = true;
	}
}

void CarroAtable::desatarSoga(int numero){
	if (numero == 1){
		atadoIzquierda = false;
	}else if (numero == 2){
		atadoDerecha = false;
	}
}

void CarroAtable::shift(){

	if (dimension->getAngulo()==ANGULO_BALANCIN_IZQ)
		this->setAngulo(-45);
	else
		this->setAngulo(ANGULO_BALANCIN_IZQ);

}