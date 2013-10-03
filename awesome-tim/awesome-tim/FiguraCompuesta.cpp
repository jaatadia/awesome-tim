#include "FiguraCompuesta.h"

FiguraCompuesta::FiguraCompuesta(const char* ID, Dimension* dim)
{
	this->dimension = dim;
}

FiguraCompuesta::~FiguraCompuesta(void)
{
	delete dimension;

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		delete (*iterFig);
	}
}

void FiguraCompuesta::cambiarPosicion(double Movx,double Movy){

	iterFig = partesFigura.begin();
	
	while( iterFig != partesFigura.end() ) {
		(*iterFig)->cambiarPosicion(Movx,Movy);
		iterFig++;
	}
	setCambio(true);
}


bool FiguraCompuesta::esMiPosicion(double x,double y){

	iterFig = partesFigura.begin();
	bool encontrada = false;
	
	while( (iterFig != partesFigura.end()) && (!encontrada) ){
		encontrada = (*iterFig)->esMiPosicion(x,y);
		iterFig++;
	}

	return encontrada;

}

bool FiguraCompuesta::intersecaCon(double X1, double Y1, double X2, double Y2){

	iterFig = partesFigura.begin();
	bool interseca = false;
	
	while( (iterFig != partesFigura.end()) && (!interseca) ){
		interseca = (*iterFig)->intersecaCon( X1, Y1, X2, Y2);
		iterFig++;
	}

	return interseca;
}


void FiguraCompuesta::dibujarEnPixel(Superficie* superficie){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujarEnPixel(superficie);
		setCambio(false);
	}

}

void FiguraCompuesta::dibujar(Superficie* superficie){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujar(superficie);
		setCambio(false);
	}
}

void FiguraCompuesta::dibujar(Superficie* super,int xIni,int yIni){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->dibujar(super,xIni,yIni);
		setCambio(false);
	}
}

void FiguraCompuesta::setTraslucido(bool flag){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->setTraslucido(flag);
	}
	setCambio(true);
}

void FiguraCompuesta::setAngulo(double angulo){

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		(*iterFig)->setAngulo(angulo);
	}	
	setCambio(true);

}


//para este no devuelve nada valido
const char* FiguraCompuesta::getID(){
	return "";
}

//para este devuelve un cuadrado que contiene a la figura
Dimension* FiguraCompuesta::getDimension(){
	return dimension;
}