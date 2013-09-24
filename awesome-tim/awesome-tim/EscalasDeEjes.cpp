#include "EscalasDeEjes.h"

EscalasDeEjes * EscalasDeEjes::instance = 0;

EscalasDeEjes * EscalasDeEjes::getInstance() {
	if (!instance)
		instance = new EscalasDeEjes();
	return instance;
}

EscalasDeEjes::EscalasDeEjes(void)
{
	escalaX=0.2;
	escalaY=0.2;
}

EscalasDeEjes::~EscalasDeEjes(void)
{
}

double EscalasDeEjes::getCantidadUnidadesLogicasX(Sint32 pixelX)
{
	return pixelX*escalaX;
}


double EscalasDeEjes::getCantidadUnidadesLogicasY(Sint32 pixelY)
{
	return pixelY*escalaY;
}

int EscalasDeEjes::getCantidadUnidadesFisicasX(double posX)
{
	return int(posX/escalaX);
}

int EscalasDeEjes::getCantidadUnidadesFisicasY(double posY)
{
	return int(posY/escalaY);
}

void EscalasDeEjes::setEscalaX(double relX){
	escalaX = relX;
}

void EscalasDeEjes::setEscalaY(double relY){
	escalaY = relY;
}