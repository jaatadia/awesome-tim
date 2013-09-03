#pragma once

#include "Botonera.h"
#include "Terreno.h"
#include "yaml-cpp/yaml.h"


class ManejadorYaml
{
public:
	
	static bool cargarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	static void guardarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	
};
