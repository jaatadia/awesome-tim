#include "FiguraSensor.h"

FiguraSensor::FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,Figura* figura):Figura("",new Cuadrado(ancho,alto,posX,posY,angulo),false){

	figuraInteractuar = figura;
	this->numInteractuar = figura->numero;
}

FiguraSensor::~FiguraSensor(void){
}
bool FiguraSensor::intersecaCon(double X1, double Y1, double X2, double Y2){
	return false;
}
bool FiguraSensor::choqueConFigura(Figura* fig){
	return false;
}
bool FiguraSensor::choqueConDimension(Dimension* dim){
	return false;
}
int FiguraSensor::getTipoFigura(){
	return FIG_SENSOR;
}
int FiguraSensor::getTipoDimension(){
	return CUADRADO;
}
void FiguraSensor::dibujar(Superficie* super){
}
Figura* FiguraSensor::clonar(){
	Dimension* dim = this->getDimension();
	return new FiguraSensor(dim->getAncho(),dim->getAlto(),dim->getX(),dim->getY(),dim->getAngulo(),(this->figuraInteractuar)->numero);
}
void FiguraSensor::accionarMotor(){

		if (figuraInteractuar->getTipoFigura() == MOTOR_RATON){
			((MotorRaton*)figuraInteractuar)->ActivarMotor();
		}
}
void FiguraSensor::cumplirObjetivo(Figura* fig){

		if (figuraInteractuar->numero == fig->numero){
			figuraInteractuar->cumplirObjetivo();
		}
}