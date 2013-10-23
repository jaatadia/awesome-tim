#include "Vela.h"

#include "Cuadrado.h"

Vela::Vela(const char* id, double posX, double posY, double angulo):FiguraCompuesta(id,new Cuadrado(ANCHO_VELA,ALTO_VELA+2*RADIO_LLAMA,posX,posY,angulo)){
	this->partesFigura = std::list<Figura*>();
	
	double posLlamaX, posLlamaY;
	calcularPosLlama(posX,posY,&posLlamaX,&posLlamaY);
	this->velaCera = new Figura(ID_VELA_CERA, new Cuadrado(ANCHO_VELA,ALTO_VELA,posX,posY,0));
	this->llama = new Figura(ID_LLAMA, new Circulo(RADIO_LLAMA,posLlamaX,posLlamaY,0));

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
	*posLlamaY = posY + (ALTO_VELA / 2 ) + RADIO_LLAMA;
}


Vela::~Vela(void){

}
