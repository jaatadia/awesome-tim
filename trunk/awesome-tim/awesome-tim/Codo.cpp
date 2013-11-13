#include "Codo.h"

Codo::Codo(double posX,double posY,double angulo):Figura(ID_CODO,new Cuadrado(ANCHO_CODO,ALTO_CODO,posX,posY,angulo)){
}

Codo::~Codo(void){
}

int Codo::getTipoFigura(){
	return CODO;
}
int Codo::getTipoDimension(){
	return CUADRADO;
}

void Codo::calcularPuntosRotados(double* x1r,double* y1r,double* x2r,double* y2r,double* x3r,double* y3r,double* x4r,double* y4r,double* x5r,double* y5r,double* x6r,double* y6r){

	double Xc = this->getDimension()->getX();
	double Yc  = this->getDimension()->getY();
	double coseno = cos(-this->getDimension()->getAngulo()*PI/180);
	double seno = sin(-this->getDimension()->getAngulo()*PI/180);
	double x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6 = 0;

	calcularPuntosSinRotar(&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&x5,&y5,&x6,&y6);
	
	*x1r = Xc + (x1-Xc)*coseno - (y1-Yc)*seno;
	*y1r = Yc + (x1-Xc)*seno + (y1-Yc)*coseno;

	*x2r = Xc + (x2-Xc)*coseno - (y2-Yc)*seno;
	*y2r = Yc + (x2-Xc)*seno + (y2-Yc)*coseno;

	*x3r = Xc + (x3-Xc)*coseno - (y3-Yc)*seno;
	*y3r = Yc + (x3-Xc)*seno + (y3-Yc)*coseno;

	*x4r = Xc + (x4-Xc)*coseno - (y4-Yc)*seno;
	*y4r = Yc + (x4-Xc)*seno + (y4-Yc)*coseno;

	*x5r = Xc + (x5-Xc)*coseno - (y5-Yc)*seno;
	*y5r = Yc + (x5-Xc)*seno + (y5-Yc)*coseno;

	*x6r = Xc + (x6-Xc)*coseno - (y6-Yc)*seno;
	*y6r = Yc + (x6-Xc)*seno + (y6-Yc)*coseno;

	if ((*x1r||*y1r||*x2r||*y2r||*x3r||*y3r||*x4r||*y4r||*x5r||*y5r||*x6r||*y6r) == NULL){
		*x1r,*y1r,*x2r,*y2r,*x3r,*y3r,*x4r,*y4r,*x5r,*y5r,*x6r,*y6r = 0;
	}

}
void Codo::calcularPuntosSinRotar(double* x1,double* y1,double* x2,double* y2,double* x3,double* y3,double* x4,double* y4,double* x5,double* y5,double* x6,double* y6){
	
	double Xc = this->getDimension()->getX();
	double Yc = this->getDimension()->getY();
	double alto = this->getDimension()->getAlto();
	double ancho = this->getDimension()->getAncho();

	*x1 = Xc;
	*y1 = Yc + alto/2;

	*x2 = Xc + ancho/6;
	*y2 = Yc + alto/6;

	*x3 = Xc + ancho/2;
	*y3 = Yc;

	*x4 = Xc + ancho/2;
	*y4 = Yc - alto/2;

	*x5 = Xc - (2*ancho)/6;
	*y5 = Yc - alto/6;

	*x6 = Xc - ancho/2;
	*y6 = Yc + alto/2;
}