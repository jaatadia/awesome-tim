#pragma once
#include "figura.h"
#include "Cuadrado.h"
#include "VistaFigAgrandable.h"

class Plataforma : public Figura{
private:
	double largo;
public:
	Plataforma(double largo,double pos_x,double pos_y,double angulo);
	~Plataforma(void);
	void agrandar();
	void achicar();
	int getTipoDimension();
	virtual double getLargo();
	virtual Figura* clonar();
};
