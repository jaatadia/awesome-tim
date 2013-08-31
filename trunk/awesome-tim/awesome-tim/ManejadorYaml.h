#pragma once

#include "Botonera.h"
#include "Terreno.h"

class ManejadorYaml
{
public:
	
	static bool cargarJuego(char* file,Botonera* botonera,Terreno* terreno);
	static void guardarJuego(char* file,Botonera* botonera,Terreno* terreno);
	
};
