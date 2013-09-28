#include "PelotaBasquet.h"

PelotaBasquet::PelotaBasquet(double r,double pos_X,double pos_Y,double angulo) : Circulo(r, pos_X, pos_Y, angulo)
{
	this->setDensidad(DENSIDAD_PELOTABASQUET);
	this->setRestitucion(RESTITUCION_PELOTABASQUET);
}

Dimension * PelotaBasquet::clonar(){
	return new PelotaBasquet(this->getRadio(), this->getX(), this->getY(), this->getAngulo());
}

PelotaBasquet::~PelotaBasquet(void)
{
}
