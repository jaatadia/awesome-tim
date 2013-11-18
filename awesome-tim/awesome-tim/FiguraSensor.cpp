#include "FiguraSensor.h"

FiguraSensor::FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,Figura* figura):Figura("",new Cuadrado(ancho,alto,posX,posY,angulo),false){

	this->figInteractuar = figura;
	this->numInteractuar = figura->numero; //este no sirve
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
	return new FiguraSensor(dim->getAncho(),dim->getAlto(),dim->getX(),dim->getY(),dim->getAngulo(),/*NECESITO EL NUMERO ACTUALIZADO*/(this->figInteractuar)->numero);
}
void FiguraSensor::accionarMotor(Figura** vector){

	if ((vector[this->numInteractuar])->getTipoFigura() == MOTOR_RATON){
		((MotorRaton*)(vector[this->numInteractuar]))->ActivarMotor();
	}

}
void FiguraSensor::cumplirObjetivo(Figura** vec,Figura* fig){

		if (this->numInteractuar == fig->numero){
			(vec[this->numInteractuar])->cumplirObjetivo();
		}
}