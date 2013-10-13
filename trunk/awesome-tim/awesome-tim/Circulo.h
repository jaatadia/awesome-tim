#pragma once

#include "dimension.h"
#include "Constantes.h"

class Circulo : public Dimension
{
private:
	double radio;
public:
	Circulo(double radio,double pos_X,double pos_Y,double angulo);
	~Circulo(void);
	double getAncho();
	double getAlto();
	double getRadio();
	void setRadio(double radio);
	bool puntoPertenece(double pos_X, double pos_Y);
	bool intersecaCon(double Xs1, double Ys1, double Xs2, double Ys2);
	int getTipoDimension(){return CIRCULO;};
	Dimension* clonar();

	virtual bool choqueConDimension(Dimension* dim);

	virtual Dimension* devolverPoligonEnvolvente();
//alrededor de que punto lo roto y el angulo
	virtual Dimension* rotarDimension(double Xrot, double yRot, double angulo);
};
