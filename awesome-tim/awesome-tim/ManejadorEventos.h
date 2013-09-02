#pragma once

#include "Juego.h"
#include "Evento.h"

class ManejadorEventos
{
public:

ManejadorEventos(void);
~ManejadorEventos(void);

bool onEvent(Juego* juego);
};

