#include "EscalasDeEjes.h"

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
	return posX/escalaX;
}

int EscalasDeEjes::getCantidadUnidadesFisicasY(double posY)
{
	return posY/escalaY;
}