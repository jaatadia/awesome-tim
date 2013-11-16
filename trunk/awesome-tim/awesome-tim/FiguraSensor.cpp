#include "FiguraSensor.h"

FiguraSensor::FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,std::list<Figura*> figuras):Figura("",new Cuadrado(ancho,alto,posX,posY,angulo),false){

	figurasInteractuar = figuras;
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
	return new FiguraSensor(dim->getAncho(),dim->getAlto(),dim->getX(),dim->getY(),dim->getAngulo(),this->figurasInteractuar);
}
void FiguraSensor::accionarMotor(){

	for (std::list<Figura*>::iterator iter = figurasInteractuar.begin();iter != figurasInteractuar.end();iter++){
		if ((*iter)->getTipoFigura() == MOTOR_RATON){
			((MotorRaton*)(*iter))->ActivarMotor();
		}
	}
}
void FiguraSensor::cumplirObjetivo(Figura* fig){

	for (std::list<Figura*>::iterator iter = figurasInteractuar.begin();iter != figurasInteractuar.end();iter++){
		if ((*iter) == fig){
			(*iter)->hacerObjetivo();
		}
	}
}