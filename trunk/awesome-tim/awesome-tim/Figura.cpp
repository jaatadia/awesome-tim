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

	X1RelCentroFig = XVector1 - dimension->getX();
	Y1RelCentroFig = YVector1 - dimension->getY();
	X2RelCentroFig = XVector2 - dimension->getX();
	Y2RelCentroFig = YVector2 - dimension->getY();

	moduloCuadrado1 = X1RelCentroFig*X1RelCentroFig + Y1RelCentroFig*Y1RelCentroFig;
	moduloCuadrado2 = X2RelCentroFig*X2RelCentroFig + Y2RelCentroFig*Y2RelCentroFig;

	productoModulo = sqrt(moduloCuadrado1*moduloCuadrado2);
	productoEscalar = X1RelCentroFig*X2RelCentroFig + Y1RelCentroFig*Y2RelCentroFig;

	variacionAngulo = acos(productoEscalar/productoModulo);

	//dado que el movimiento puede haber sido horario o antihorario y ambos dan el mismo valor averiguo hacia que lado fue
	bool esPositivo = anguloEsPositivo(X1RelCentroFig,Y1RelCentroFig,X2RelCentroFig,Y2RelCentroFig);

	if (!esPositivo)
		variacionAngulo = -variacionAngulo;

	//Paso el angulo a grados desde radianes
	variacionAngulo = (variacionAngulo*180/PI);

	dimension->setAngulo( dimension->getAngulo() + variacionAngulo);
	//cambio la vista!
	setCambio(true);

}

bool Figura::esMiPosicion(double x,double y)
{
	return dimension->puntoPertenece( x, y);
}

void Figura::dibujarEnPixel(Superficie* super,EscalasDeEjes* escalas){
	myVista->dibujarEnPixel(super,escalas);
}

void Figura::dibujar(Superficie* super,EscalasDeEjes* escalas){
	myVista->dibujar(super,escalas);
}

int Figura::obtenerCuadranteDeClick(double X, double Y){

if (X>=0 && Y>=0)
	return 4;

if (X<=0 && Y>=0)
	return 3;

if (X<=0 && Y<=0)
	return 2;

if (X>=0 && Y<=0)
	return 1;

return -1;
}

bool Figura::anguloEsPositivo(double X1, double Y1, double X2, double Y2){
	
	int cuadrante1 = obtenerCuadranteDeClick(X1,Y1);
	int cuadrante2 = obtenerCuadranteDeClick(X2,Y2);
	
	Recta recta1(X1,Y1,0,0);

	if (cuadrante1 == cuadrante2){
		//verificar con las rectas
		switch (cuadrante1){
			case 1: case 4:
			{
				if(recta1.puntoPorDebajo(X2,Y2))
					return false;
				else
					return true;
				break;
			}
			case 2: case 3:
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
			case 1:
			{
				if (cuadrante2 == 2)
					return true;
				else
					if (cuadrante2 == 4)
						return false;
				break;
			}
			case 2:
			{
				if (cuadrante2 == 3)
					return true;
				else
					if (cuadrante2 == 1)
						return false;
				break;
			}
			case 3:
			{
				if (cuadrante2 == 4)
					return true;
				else
					if (cuadrante2 == 2)
						return false;
				break;
			}
			case 4:
			{
				if (cuadrante2 == 1)
					return true;
				else
					if (cuadrante2 == 3)
						return false;
				break;
			}
		}
	//por defecto asumo que es positivo
	return true;
}
