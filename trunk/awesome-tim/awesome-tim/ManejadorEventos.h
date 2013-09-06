#pragma once

#include <iostream>
#include "SDL.h"
#include "EscalasDeEjes.h"


class ManejadorEventos
{
private:
	static EscalasDeEjes* escalasDeEjes;

public:

ManejadorEventos(void);
~ManejadorEventos(void);

virtual void actuarVentana(Uint32 IDventana,SDL_WindowEvent evento,EscalasDeEjes* escalas);

virtual void quit();

virtual bool categorizarEvento(SDL_Event evento);
};

