#pragma once

#include "Botonera.h"
#include "Terreno.h"
#include "yaml-cpp/yaml.h"


class ManejadorYaml{
public:
	
	static bool cargarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	static bool guardarJuego(const char* file,Botonera* botonera,Terreno* terreno);

private:

	static void cargar_botones(const YAML::Node& nodoBotonera, Botonera* botonera);
	static void cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno);
	static void cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno);
	static Dimension* obtener_dimension(const YAML::Node& Figura,const char* tipo_dimension);
	static Figura* cargarFigura(const char* tipo_figura,const char* imagen,int posX,int posY,Dimension* dimension);



};
