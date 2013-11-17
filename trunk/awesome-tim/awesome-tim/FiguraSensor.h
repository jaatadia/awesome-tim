#pragma once
#include "figura.h"
#include <list>
#include "MotorRaton.h"

class FiguraSensor :
	public Figura
{
private:
	Figura* figuraInteractuar;
	//int ID;

public:
	FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,Figura* figura);
	~FiguraSensor(void);
	virtual int getTipoFigura();
	virtual int getTipoDimension();
	Figura* clonar();

	virtual void accionarMotor();
	virtual void cumplirObjetivo(Figura* fig);

	//FIX: espero que sean estas las q tengo q hacer false (?) 
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);
	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);
	virtual	void dibujar(Superficie* super);
};
