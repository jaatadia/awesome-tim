#pragma once
#include "SDL.h"
/*
Guarda las escalas de los ejes (unidades logicas / pixels ) y se ocupa de convertir respecto a ellas
la posicion de un pixel en una posicion logica y viceversa
*/

class EscalasDeEjes
{
private:
	double escalaX,escalaY;
	EscalasDeEjes(void);
	static EscalasDeEjes * instance;

public:
	~EscalasDeEjes(void);
	static EscalasDeEjes * getInstance();

	void setEscalaX(double relX);
	void setEscalaY(double relY);

	double getCantidadUnidadesLogicasX(Sint32 pixelX);
	double getCantidadUnidadesLogicasY(Sint32 pixelY);

	int getCantidadUnidadesFisicasX(double posX);
	int getCantidadUnidadesFisicasY(double posY);

};
