#include "ManejadorYaml.h"
#include <fstream>

bool ManejadorYaml::cargarJuego(char* file,Botonera* botonera,Terreno* terreno)
{
	std::ifstream fin("archivoYaml.yaml");
	YAML::Parser parser(fin);
	return false;
}