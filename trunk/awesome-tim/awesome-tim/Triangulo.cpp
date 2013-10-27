#include "Triangulo.h"
#include <cmath>
#include "Constantes.h"

Triangulo::Triangulo(double X, double Y, double angulo, double base,double altura): Dimension(X,Y,angulo){
	this->base = base;
	this->altura = altura;

	double extra = 0;

	x1 = 0;
	y1 = -(altura/2);

	x2 = -(base/2);
	y2 = (altura/2);

	x3 = +base/2;
	y3 = (altura/2);

}

Triangulo::~Triangulo(void)
{
}

bool Triangulo::puntoPertenece(double tX, double tY){
	
	double angle = -(PI*this->getAngulo())/180.0;
	double tx1 = getX() + x1;//((x1) * cos(angle)) - ((y1) * sin(angle));
	double ty1 = getY() + y1;//((x1) * sin(angle)) + ((y1) * cos(angle));
	double tx2 = getX() + x2;//((x2) * cos(angle)) - ((y2) * sin(angle));
	double ty2 = getY() + y2;//((x2) * sin(angle)) + ((y2) * cos(angle));
	double tx3 = getX() + x3;//((x3) * cos(angle)) - ((y3) * sin(angle));
	double ty3 = getY() + y3;//((x3) * sin(angle)) + ((y3) * cos(angle));


	double X = getX() + ((tX-getX()) * cos(-angle)) - ((tY-getY()) * sin(-angle));
	double Y = getY() + ((tX-getX()) * sin(-angle)) + ((tY-getY()) * cos(-angle));

	bool signoOK = true;
	double signo;
	double signoClick;

	signo = enRecta(getX(),getY(),tx1,ty1,tx2,ty2);
	signoClick = enRecta(X,Y,tx1,ty1,+tx2,+ty2);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	if(!signoOK) return false;

	signo = enRecta(getX(),getY(),tx1,ty1,tx3,ty3);
	signoClick = enRecta(X,Y,tx1,ty1,+tx3,+ty3);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	if(!signoOK) return false;

	signo = enRecta(getX(),getY(),tx2,ty2,tx3,ty3);
	signoClick = enRecta(X,Y,tx2,ty2,+tx3,+ty3);
	if(signoClick<0) signoOK = (signo<0);
	else if(signoClick>0) signoOK = (signo>0);
	
	return signoOK;
}

double Triangulo::getAncho(void){
	return base;
}

double Triangulo::getAlto(void){
	return altura;
}

double Triangulo::enRecta(double x,double y,double x0,double y0,double x1,double y1){
	//return (((x-x0)/(x1-x0))-((y-y0)/(y1-y0)));
	return (((x-x0)*(y1-y0))-((y-y0)*(x1-x0)));
}

Dimension* Triangulo::clonar(){
	return new Triangulo(getX(),getY(),getAngulo(),base,altura);
}

bool Triangulo::intersecaCon(double XsUno, double YsUno, double XsDos, double YsDos){

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

	Segmento segPropio1(x1 + getX(), y1 + getY(), x2 + getX(), y2 + getY());
	Segmento segPropio2(x2 + getX(), y2 + getY(), x3 + getX(), y3 + getY());
	Segmento segPropio3(x3 + getX(), y3 + getY(), x1 + getX(), y1 + getY());

	if ( segPropio1.intersecaCon(segExterno) || segPropio2.intersecaCon(segExterno) ||	segPropio3.intersecaCon(segExterno) ){
		return true;
	}

	delete segExterno;

	return false;
}

bool Triangulo::choqueConDimension(Dimension* dim){

	Dimension* dimAChocar;
	//rota al reves mio  la que me pasaron, solo si no estoy rotado de verdad
	if (this->getAnguloReal() != this->getAngulo()){
		double angle = -(PI*this->getAngulo())/180.0;
		dimAChocar = dim->rotarDimension(getX(),getY(),- this->getAngulo());
	}else{
		dimAChocar = dim->clonar();
	}
	//me fijo si alguna de las aristas de mi triangulo corta la otra dimension
	bool interseca = false;

	if( dimAChocar->intersecaCon(x1 + getX(), y1 + getY(), x2 + getX(), y2 + getY()) ||
		dimAChocar->intersecaCon(x2 + getX(), y2 + getY(), x3 + getX(), y3 + getY()) ||
		dimAChocar->intersecaCon(x1 + getX(), y1 + getY(), x3 + getX(), y3 + getY()) ){
		interseca = true;
	}

	delete dimAChocar;
	
	return interseca;
}

Dimension* Triangulo::rotarDimension(double xRot, double yRot, double angulo){

	double angle = (PI*angulo)/180.0;

	Triangulo* triangADevolver = (Triangulo*)this->clonar();

//roto la posicion y cada vertice		
	triangADevolver->setX( xRot + ((this->getX()-xRot) * cos(-angle)) - ((this->getY()-yRot) * sin(-angle)) );
	triangADevolver->setY( yRot + ((this->getX()-xRot) * sin(-angle)) + ((this->getY()-yRot) * cos(-angle)) );

//los vertices alrededor del cero porque estan dados relativos al centro de la dimension
	x1 = x1 * cos(-angle) - y1 * sin(-angle);
	y1 = x1 * sin(-angle) + y1 * cos(-angle);

	x2 = x2 * cos(-angle) - y2 * sin(-angle);
	y2 = x2 * sin(-angle) + y2 * cos(-angle);

	x3 = x3 * cos(-angle) - y3 * sin(-angle);
	y3 = x3 * sin(-angle) + y3 * cos(-angle);

//tengo que hacer esto porque pueden estar desfasados (antes de la primera rotacion)		
	triangADevolver->setAngulo( triangADevolver->getAnguloReal() );

	triangADevolver->setAngulo( triangADevolver->getAngulo() + angulo );
	triangADevolver->setAnguloReal( triangADevolver->getAnguloReal() + angulo );

	return triangADevolver;
}