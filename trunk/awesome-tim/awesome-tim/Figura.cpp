#include "Figura.h"
#include "Recta.h"
#include "Constantes.h"
#include <math.h>

Figura::Figura(const char* ID,Dimension* dim){
	this->ID = ID;
	this->dimension = dim;
	this->setCambio(true);
	this->myVista = new VistaFigura(this);
}

Figura::~Figura(void){
	delete myVista;
	delete dimension;
}

void Figura::cambiarPosicion(double x,double y)
{
	dimension->setX( dimension->getX() + x);
	dimension->setY( dimension->getY() + y);
}

void Figura::cambiarAngulo(double XVector1,double YVector1,double XVector2,double YVector2){
	//producto escalar de ambos / producto de modulos = coseno del angulo menor entre vectores
	double X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig;
	double moduloCuadrado1, moduloCuadrado2;
	double productoModulo;
	double productoEscalar;
	double variacionAngulo;
	double divisionEscalarModulo;

	X1RelCentroFig = XVector1 - dimension->getX();
	Y1RelCentroFig = YVector1 - dimension->getY();
	X2RelCentroFig = XVector2 - dimension->getX();
	Y2RelCentroFig = YVector2 - dimension->getY();

	moduloCuadrado1 = X1RelCentroFig*X1RelCentroFig + Y1RelCentroFig*Y1RelCentroFig;
	moduloCuadrado2 = X2RelCentroFig*X2RelCentroFig + Y2RelCentroFig*Y2RelCentroFig;
	//if necesario o puede romperse la raiz, en resumen, si pasa por el centro no cambio el angulo
	if ((moduloCuadrado1 != 0) && (moduloCuadrado2 != 0)){
		productoModulo = sqrt(moduloCuadrado1*moduloCuadrado2);

		productoEscalar = X1RelCentroFig*X2RelCentroFig + Y1RelCentroFig*Y2RelCentroFig;
		
		//por que si por redondeo extraño es mayor que 1 devuelve NaN el acos. 
		divisionEscalarModulo = productoEscalar/productoModulo;

		if (divisionEscalarModulo > 1)
			divisionEscalarModulo = 0.99999999999999999999999999999999999;
	
		variacionAngulo = acos(divisionEscalarModulo);

		//dado que el movimiento puede haber sido horario o antihorario y ambos dan el mismo valor averiguo hacia que lado fue
		bool esPositivo = anguloEsPositivo(X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig);

		if (!esPositivo)
			variacionAngulo = -variacionAngulo;

		//Paso el angulo a grados desde radianes
		variacionAngulo = (variacionAngulo*180/PI);

		dimension->setAngulo(dimension->getAngulo() + variacionAngulo);

		while(dimension->getAngulo() >= 360) dimension->setAngulo( dimension->getAngulo() - 360);
		while(dimension->getAngulo() < 0) dimension->setAngulo( dimension->getAngulo() + 360);
		//cambio la vista!
		setCambio(true);
	}
}

bool Figura::esMiPosicion(double x,double y,EscalasDeEjes* escalas)
{

	double miX = x;
	double miY = y;

	//comentar esto para que ande como antes (acordarse de cambiar tambien VistaFigura.cpp redraw)
	double miAngulo = (dimension->getAngulo())*PI/180;
	double centroXReal = escalas->getCantidadUnidadesFisicasX(this->dimension->getX()+0.5)+0.0;
	double centroYReal = escalas->getCantidadUnidadesFisicasY(this->dimension->getY()+0.5)+0.0;
	double xReal = escalas->getCantidadUnidadesFisicasX(x+0.5)+0.0;
	double yReal = escalas->getCantidadUnidadesFisicasY(y+0.5)+0.0;
	
	double tempX = centroXReal + (xReal - centroXReal)*cos(miAngulo) - (yReal - centroYReal)*sin(miAngulo);
	double tempY = centroYReal + (xReal - centroXReal)*sin(miAngulo) + (yReal - centroYReal)*cos(miAngulo);
	tempX = escalas->getCantidadUnidadesLogicasX(tempX);
	tempY = escalas->getCantidadUnidadesLogicasY(tempY);

	miAngulo*=-1;
	double cX = dimension->getX();
	double cY = dimension->getY();

	miX = cX + (tempX - cX)*cos(miAngulo) - (tempY - cY)*sin(miAngulo);
	miY = cY + (tempX - cX)*sin(miAngulo) + (tempY - cY)*cos(miAngulo);
	//terminar de comentar aca

	return dimension->puntoPertenece( miX, miY);
}

void Figura::dibujarEnPixel(Superficie* super,EscalasDeEjes* escalas){
	myVista->dibujarEnPixel(super,escalas);
}

void Figura::dibujar(Superficie* super,EscalasDeEjes* escalas){
	myVista->dibujar(super,escalas);
}

int Figura::obtenerCuadranteDeClick(double X, double Y){

if (X>=0 && Y>=0)
	return CUADRANTE4;

if (X<=0 && Y>=0)
	return CUADRANTE3;

if (X<=0 && Y<=0)
	return CUADRANTE2;

if (X>=0 && Y<=0)
	return CUADRANTE1;

return -1;
}

bool Figura::anguloEsPositivo(double X1, double Y1, double X2, double Y2){
	
	int cuadrante1 = obtenerCuadranteDeClick(X1,Y1);
	int cuadrante2 = obtenerCuadranteDeClick(X2,Y2);
	
	Recta recta1(X1,Y1,0,0);

	if (cuadrante1 == cuadrante2){
		//verificar con las rectas
		switch (cuadrante1){
			case CUADRANTE1: case CUADRANTE4:
			{
				if(recta1.puntoPorDebajo(X2,Y2))
					return false;
				else
					return true;
				break;
			}
			case CUADRANTE2: case CUADRANTE3:
			{
				if(recta1.puntoPorDebajo(X2,Y2))
					return true;
				else
					return false;
				break;
			}
		}
	}else
		switch (cuadrante1){
			case CUADRANTE1:
			{
				if (cuadrante2 == CUADRANTE2)
					return true;
				else
					if (cuadrante2 == CUADRANTE4)
						return false;
				break;
			}
			case CUADRANTE2:
			{
				if (cuadrante2 == CUADRANTE3)
					return true;
				else
					if (cuadrante2 == CUADRANTE1)
						return false;
				break;
			}
			case CUADRANTE3:
			{
				if (cuadrante2 == CUADRANTE4)
					return true;
				else
					if (cuadrante2 == CUADRANTE2)
						return false;
				break;
			}
			case CUADRANTE4:
			{
				if (cuadrante2 == CUADRANTE1)
					return true;
				else
					if (cuadrante2 == CUADRANTE3)
						return false;
				break;
			}
		}
	//por defecto asumo que es positivo
	return true;
}


const char* Figura::getID(){
	return (this->ID.c_str());
};
Dimension* Figura::getDimension(){
	return (this->dimension);
};

bool Figura::intersecaCon(double X1, double Y1, double X2, double Y2){
	return dimension->intersecaCon( X1, Y1, X2, Y2);
}

Figura* Figura::clonar(){
	return new Figura(ID.c_str(),dimension->clonar());
}