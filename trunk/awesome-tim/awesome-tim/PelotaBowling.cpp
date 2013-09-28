#include "PelotaBowling.h"

PelotaBowling::PelotaBowling(double r,double pos_X,double pos_Y,double angulo) : Circulo(r, pos_X, pos_Y, angulo)
{
	this->setDensidad(DENSIDAD_PELOTABOWLING);
	this->setRestitucion(RESTITUCION_PELOTABOWLING);
}

Dimension * PelotaBowling::clonar(){
	return new PelotaBowling(this->getRadio(), this->getX(), this->getY(), this->getAngulo());
}

PelotaBowling::~PelotaBowling(void)
{
}
