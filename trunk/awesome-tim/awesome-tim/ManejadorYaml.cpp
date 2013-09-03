#include "ManejadorYaml.h"
#include <fstream>

bool ManejadorYaml::cargarJuego(const char* file,Botonera* botonera,Terreno* terreno)
{
	std::ifstream fin("archivoYaml.yaml");
	YAML::Parser parser(fin);
	return false;
}

void ManejadorYaml::guardarJuego(const char* file,Botonera* botonera,Terreno* terreno){
}