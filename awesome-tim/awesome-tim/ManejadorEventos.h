#pragma once

#include <iostream>
#include "SDL.h"
#include "EscalasDeEjes.h"


class ManejadorEventos
{
private:

public:

ManejadorEventos(void);
~ManejadorEventos(void);

virtual void actuarVentana(Uint32 IDventana,SDL_WindowEvent evento);

virtual void quit();

virtual bool categorizarEvento(SDL_Event evento);
};

