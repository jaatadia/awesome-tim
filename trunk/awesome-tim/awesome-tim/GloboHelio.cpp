#include "GloboHelio.h"

GloboHelio::GloboHelio(double r, double pos_X, double pos_Y, double angulo) : Circulo(r, pos_X, pos_Y, angulo)
{
}

Dimension * GloboHelio::clonar(){
	return new GloboHelio(this->getRadio(), this->getX(), this->getY(), this->getAngulo());
}

GloboHelio::~GloboHelio(void)
{
}
