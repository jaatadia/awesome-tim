#include "Vela.h"

#include "Cuadrado.h"

Vela::Vela(const char* id, double posX, double posY, double angulo):FiguraCompuesta(id,new Cuadrado(ANCHO_VELA,ALTO_VELA+2*RADIO_LLAMA,posX,posY,angulo)){
	this->partesFigura = std::list<Figura*>();
	
	double posLlamaX, posLlamaY;
	calcularPosLlama(posX,posY,&posLlamaX,&posLlamaY);
	this->velaCera = new Figura(ID_VELA_CERA, new Cuadrado(ANCHO_VELA,ALTO_VELA,posX,posY+RADIO_LLAMA,0));
	this->llama = new Figura(ID_LLAMA, new Circulo(RADIO_LLAMA,posLlamaX,posLlamaY+RADIO_LLAMA,0));

	this->partesFigura.push_back(this->velaCera);
	this->partesFigura.push_back(this->llama);

	this->inicAngulosCentro();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		angulos.push_back((*iterFig)->getDimension()->getAngulo());
	}
	this->setAngulo(angulo);
}

void Vela::calcularPosLlama(double posX,double posY,double* posLlamaX,double* posLlamaY){
	*posLlamaX = posX;
	*posLlamaY = posY - (ALTO_VELA / 2 ) - RADIO_LLAMA;
}

Vela::~Vela(void){}

Figura* Vela::clonar(){

	Cuadrado* dim = (Cuadrado*) this->getDimension();
	Figura* vela = new Vela("",dim->getX(),dim->getY(),dim->getAngulo());
	this->completarInteraccionesPosibles(vela);
	return vela;
}


int Vela::getTipoDimension(){
	return CUADRADO;
}

int Vela::getTipoFigura(){
	return VELA;
}

Figura* Vela::getVelaCera(){
	return this->velaCera;
}

Figura* Vela::getLlama(){
	return this->llama;
}

bool Vela::cortaSoga(){
	return true;
}


bool Vela::pinchaGlobo(Dimension* dim){
	return true;
}
void Vela::getCuadradoCortante(double* x1,double* y1,double* x2,double* y2){

	float X = this->llama->getDimension()->getX();
	float Y = this->llama->getDimension()->getY();
	float ancho = this->llama->getDimension()->getAncho();
	float alto = this->llama->getDimension()->getAlto();
	*x1 = X - (ancho/2);
	*y1 = Y - (alto/2);
	*x2 = X + (ancho/2);
	*y2 = Y + (alto/2);
}