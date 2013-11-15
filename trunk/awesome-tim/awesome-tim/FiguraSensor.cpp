#include "FiguraSensor.h"

FiguraSensor::FiguraSensor(double ancho,double alto,double posX,double posY,double angulo):Figura("",new Cuadrado(ancho,alto,posX,posY,angulo),false){
}

FiguraSensor::~FiguraSensor(void){

	for (std::list<Figura*>::iterator iter = (this->figurasInteractuar).begin();iter != (this->figurasInteractuar).end();iter++){
		delete (*iter);
	}
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
};