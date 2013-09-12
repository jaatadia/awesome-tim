#include "Cuadrado.h"


Cuadrado::Cuadrado(double ancho,double alto,double X, double Y, double angulo): Dimension(X,Y,angulo) {
	this->ancho = ancho;
	this->alto = alto;

	diagonal = sqrt(alto*alto + ancho*ancho)/2;
	anguloDiagonal = 45;

	setAngulo(angulo);
}

Cuadrado::~Cuadrado(void){
}

double Cuadrado::getAncho(){
	return ancho;
}

double Cuadrado::getAlto(){
	return alto;
}

bool Cuadrado::puntoPertenece(double X, double Y){

	bool pertenece = true;

	Recta r1(vertice1.getX(), vertice1.getY(), vertice2.getX(), vertice2.getY());
	Recta r2(vertice2.getX(), vertice2.getY(), vertice3.getX(), vertice3.getY());
	Recta r3(vertice3.getX(), vertice3.getY(), vertice4.getX(), vertice4.getY());
	Recta r4(vertice4.getX(), vertice4.getY(), vertice1.getX(), vertice1.getY());

	double XrelCentro,YrelCentro;

	XrelCentro = X - getX();
	YrelCentro = Y - getY();

	if (r4.vertical()){
		if (r4.puntoADerecha(XrelCentro,YrelCentro))
			pertenece = false;
	}
	else{
		if (r4.puntoPorArriba(XrelCentro,YrelCentro))
			pertenece = false;
	}

	if (r2.vertical()){
		if (r2.puntoAIzquierda(XrelCentro,YrelCentro))
			pertenece = false;
	}
	else{
		if (r2.puntoPorDebajo(XrelCentro,YrelCentro))
			pertenece = false;
	}

	if (r1.puntoPorArriba(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	if (r3.puntoPorDebajo(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	return pertenece;
}

void Cuadrado::setAngulo(double anguloRecibido){

	this->angulo = anguloRecibido;

	while (angulo >= 360) angulo -= 360; // o podria aumentar y aumentar
	while (angulo < 0) angulo += 360;

	//reduzco a 90 grados ya que despues se repite el area ocupada y convierto a radianes 
	while (anguloRecibido >= 90) anguloRecibido-=90;

	double ang = (anguloRecibido*PI/180);
	//si el angulo es cero falla el calculo en las rectas mas adelante por redondeos
	if (ang != 0 && angulo != 0){
		vertice1.setX(diagonal*cos(ang+PI/4+0*PI/2));
		vertice1.setY(-diagonal*sin(ang+PI/4+0*PI/2));

		vertice2.setX(diagonal*cos(ang+PI/4+1*PI/2));
		vertice2.setY(-diagonal*sin(ang+PI/4+1*PI/2));

		vertice3.setX(diagonal*cos(ang+PI/4+2*PI/2));
		vertice3.setY(-diagonal*sin(ang+PI/4+2*PI/2));

		vertice4.setX(diagonal*cos(ang+PI/4+3*PI/2));
		vertice4.setY(-diagonal*sin(ang+PI/4+3*PI/2));

	}else{
		RESETEAR_VERTICES: 
		vertice1.setX(ancho/2);
		vertice1.setY(-alto/2);

		vertice2.setX(-ancho/2);
		vertice2.setY(-alto/2);

		vertice3.setX(-ancho/2);
		vertice3.setY(alto/2);

		vertice4.setX(ancho/2);
		vertice4.setY(alto/2);
	}

	//por algun motivo a veces el vertice 4 termina a la izquierda del 1 en lugar de arriba, cosa que geometricamente no puede pasar
	//aca lo corrijo y los pongo alineados verticales, ya que es el unico caso donde esto se da
	//tambien puede pasar con los vertices 2 y 3 y/o pueden desfasarse verticalmente

	if ( (vertice4.getX() < vertice1.getX()) || (vertice3.getX() < vertice2.getX()) ||
		(vertice1.getY() < vertice2.getY()) || (vertice4.getY() < vertice3.getY())){

		goto RESETEAR_VERTICES;
	}


}