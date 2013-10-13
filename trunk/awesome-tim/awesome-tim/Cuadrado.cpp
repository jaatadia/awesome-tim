#include "Cuadrado.h"


Cuadrado::Cuadrado(double ancho,double alto,double X, double Y, double angulo): Dimension(X,Y,angulo) {
	this->ancho = ancho;
	this->alto = alto;

	vertice1.setX(ancho/2);
	vertice1.setY(-alto/2);

	vertice2.setX(-ancho/2);
	vertice2.setY(-alto/2);

	vertice3.setX(-ancho/2);
	vertice3.setY(alto/2);

	vertice4.setX(ancho/2);
	vertice4.setY(alto/2);
}

Cuadrado::~Cuadrado(void){
}

double Cuadrado::getAncho(){
	return ancho;
}

double Cuadrado::getAlto(){
	return alto;
}

bool Cuadrado::puntoPertenece(double XPunto, double YPunto){

	bool pertenece = true;

	Recta r1(vertice1.getX(), vertice1.getY(), vertice2.getX(), vertice2.getY());
	Recta r2(vertice2.getX(), vertice2.getY(), vertice3.getX(), vertice3.getY());
	Recta r3(vertice3.getX(), vertice3.getY(), vertice4.getX(), vertice4.getY());
	Recta r4(vertice4.getX(), vertice4.getY(), vertice1.getX(), vertice1.getY());

	double Xrotado;
	double Yrotado;

	//si no estoy rotado de verdad, roto el punto al reves de como esta el cuadrado
	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		Xrotado = getX() + ((XPunto-getX()) * cos(-angle)) - ((YPunto-getY()) * sin(-angle));
		Yrotado = getY() + ((XPunto-getX()) * sin(-angle)) + ((YPunto-getY()) * cos(-angle));
	}else{
		Xrotado = XPunto;
		Yrotado = YPunto;
	}

	double XrelCentro =  Xrotado - this->getX();
	double YrelCentro =  Yrotado - this->getY();
	//verifico lado por lado

	if (r4.puntoADerecha(XrelCentro,YrelCentro)){
		pertenece = false;
	}

	if (r2.puntoAIzquierda(XrelCentro,YrelCentro)){
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


Dimension* Cuadrado::clonar(){

	Cuadrado* cuadADevolver = new Cuadrado(ancho,alto,getX(),getY(),angulo);

	cuadADevolver->setAnguloReal( this->getAnguloReal() );

	//y todos los vertices
	cuadADevolver->setX1( this->getX1() );
	cuadADevolver->setY1( this->getY1() );

	cuadADevolver->setX2( this->getX2() );
	cuadADevolver->setY2( this->getY2() );

	cuadADevolver->setX3( this->getX3() );
	cuadADevolver->setY3( this->getY3() );

	cuadADevolver->setX4( this->getX4() );
	cuadADevolver->setY4( this->getY4() );

	return (Dimension*) cuadADevolver;
}

bool Cuadrado::intersecaCon(double XsUno, double YsUno, double XsDos, double YsDos){

	double Xs1;
	double Ys1;
	double Xs2;
	double Ys2;

	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		Xs1 = getX() + ((XsUno-getX()) * cos(-angle)) - ((YsUno-getY()) * sin(-angle));
		Ys1 = getY() + ((XsUno-getX()) * sin(-angle)) + ((YsUno-getY()) * cos(-angle));
		Xs2 = getX() + ((XsDos-getX()) * cos(-angle)) - ((YsDos-getY()) * sin(-angle));
		Ys2 = getY() + ((XsDos-getX()) * sin(-angle)) + ((YsDos-getY()) * cos(-angle));
	}else{
		Xs1 = XsUno;
		Ys1 = YsUno;
		Xs2 = XsDos;
		Ys2 = YsDos;
	}

	Segmento* segExterno = new Segmento(Xs1, Ys1, Xs2, Ys2);


	Segmento segPropio1(vertice1.getX() + getX(), vertice1.getY() + getY(), vertice2.getX() + getX(), vertice2.getY() + getY());
	Segmento segPropio2(vertice2.getX() + getX(), vertice2.getY() + getY(), vertice3.getX() + getX(), vertice3.getY() + getY());
	Segmento segPropio3(vertice3.getX() + getX(), vertice3.getY() + getY(), vertice4.getX() + getX(), vertice4.getY() + getY());
	Segmento segPropio4(vertice4.getX() + getX(), vertice4.getY() + getY(), vertice1.getX() + getX(), vertice1.getY() + getY()); 

	if	 (segPropio1.intersecaCon(segExterno) || segPropio2.intersecaCon(segExterno) ||
		segPropio3.intersecaCon(segExterno) || segPropio4.intersecaCon(segExterno)){
		return true;
	}

	delete segExterno;

	return false;
}


void Cuadrado::setAncho(double nuevoLargo){
	this->ancho = nuevoLargo;

	vertice1.setX(ancho/2);
	vertice1.setY(-alto/2);

	vertice2.setX(-ancho/2);
	vertice2.setY(-alto/2);

	vertice3.setX(-ancho/2);
	vertice3.setY(alto/2);

	vertice4.setX(ancho/2);
	vertice4.setY(alto/2);
}


bool Cuadrado::choqueConDimension(Dimension* dim){

	Dimension* dimAChocar;
	//rota al reves mio  la que me pasaron, solo si no estoy rotado de verdad
	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		dimAChocar = dim->rotarDimension(getX(),getY(),- this->getAngulo());
	}else{
		dimAChocar = dim->clonar();
	}
	//me fijo si alguna de sus aristas corta la otra dimension
	bool interseca = false;

	if( dimAChocar->intersecaCon(vertice1.getX() + getX(),vertice1.getY() + getY(),vertice2.getX() + getX(),vertice2.getY() + getY()) ||
		dimAChocar->intersecaCon(vertice2.getX() + getX(),vertice2.getY() + getY(),vertice3.getX() + getX(),vertice3.getY() + getY()) ||
		dimAChocar->intersecaCon(vertice3.getX() + getX(),vertice3.getY() + getY(),vertice4.getX() + getX(),vertice4.getY() + getY()) ||
		dimAChocar->intersecaCon(vertice4.getX() + getX(),vertice4.getY() + getY(),vertice1.getX() + getX(),vertice1.getY() + getY()) ){
		interseca = true;
	}

	delete dimAChocar;
	
	return interseca;

}

Dimension* Cuadrado::rotarDimension(double xRot, double yRot, double angulo){

	double angle = (PI*angulo)/180.0;

	Cuadrado* cuadADevolver = (Cuadrado*)this->clonar();

//roto la posicion y cada vertice		
	cuadADevolver->setX( xRot + ((this->getX()-xRot) * cos(-angle)) - ((this->getY()-yRot) * sin(-angle)) );
	cuadADevolver->setY( yRot + ((this->getX()-xRot) * sin(-angle)) + ((this->getY()-yRot) * cos(-angle)) );
//los vertices alrededor del cero porque estan dados relativos al centro de la dimension
	cuadADevolver->setX1( 0 + ((vertice1.getX()-0) * cos(-angle)) - ((vertice1.getY()-0) * sin(-angle)) );
	cuadADevolver->setY1( 0 + ((vertice1.getX()-0) * sin(-angle)) + ((vertice1.getY()-0) * cos(-angle)) );

	cuadADevolver->setX2( 0 + ((vertice2.getX()-0) * cos(-angle)) - ((vertice2.getY()-0) * sin(-angle)) );
	cuadADevolver->setY2( 0 + ((vertice2.getX()-0) * sin(-angle)) + ((vertice2.getY()-0) * cos(-angle)) );

	cuadADevolver->setX3( 0 + ((vertice3.getX()-0) * cos(-angle)) - ((vertice3.getY()-0) * sin(-angle)) );
	cuadADevolver->setY3( 0 + ((vertice3.getX()-0) * sin(-angle)) + ((vertice3.getY()-0) * cos(-angle)) );

	cuadADevolver->setX4( 0 + ((vertice4.getX()-0) * cos(-angle)) - ((vertice4.getY()-0) * sin(-angle)) );
	cuadADevolver->setY4( 0 + ((vertice4.getX()-0) * sin(-angle)) + ((vertice4.getY()-0) * cos(-angle)) );
//tengo que hacer esto porque pueden estar desfasdos (antes de la primera rotacion)		
	cuadADevolver->setAngulo( cuadADevolver->getAnguloReal() );

	cuadADevolver->setAngulo( cuadADevolver->getAngulo() + angulo );
	cuadADevolver->setAnguloReal( cuadADevolver->getAnguloReal() + angulo );

	return cuadADevolver;
}