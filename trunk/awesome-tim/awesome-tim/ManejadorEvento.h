#pragma once

#include "Juego.h"
#include "Evento.h"

class ManejadorEvento
{
public:
	virtual void onEvento(Evento* evento,Juego* juego)=0;
};
