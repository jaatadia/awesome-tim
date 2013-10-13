#pragma once

#include "Dimension.h"
#include "Constantes.h"

class PoligonoRegular: public Dimension
{

private:
	double radio;
	int vertices;
	double vectorX[100];
	double vectorY[100];

public:
	PoligonoRegular(double x, double y,double radio,int vert,double angulo);
	~PoligonoRegular(void);
	
	bool puntoPertenece(double X, double Y);
	double getAncho(void);
	double getAlto(void);

	double getRadio();
	double getCantVertices();
	
	bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual int getTipoDimension(){return POLIGONOREGULAR;}
	Dimension* clonar();

	virtual bool choqueConDimension(Dimension* dim);

	virtual Dimension* rotarDimension(double Xrot, double yRot, double angulo);

	virtual void setVertX(int i, double x);
	virtual void setVertY(int i, double y);

	virtual double getVerticeX(int i);
	virtual double getVerticeY(int i);

private:
	double enRecta(double x,double y,double x0,double y0,double x1,double y1);

};
