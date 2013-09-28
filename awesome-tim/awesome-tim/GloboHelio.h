#pragma once
#include "circulo.h"

class GloboHelio : public Circulo
{
private:
	GloboHelio(void);
public:
	GloboHelio(double r,double pos_X,double pos_Y,double angulo);
	~GloboHelio(void);

	virtual int getTipoDimension(){return GLOBOHELIO;}
	virtual Dimension * clonar();
};
