#pragma once
#include "circulo.h"

class PelotaBowling : public Circulo
{
private:
	PelotaBowling(void);
public:
	PelotaBowling(double r,double pos_X,double pos_Y,double angulo);
	~PelotaBowling(void);

	virtual int getTipoDimension(){return PELOTABOWLING;}
	virtual Dimension * clonar();
};
