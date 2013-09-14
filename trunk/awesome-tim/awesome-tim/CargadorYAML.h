#pragma once

#include "yaml-cpp/yaml.h"

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Constantes.h"

#include "BotoneraController.h"
#include "Terreno.h"
#include "Posicion.h"

#include "Cuadrado.h"
#include "Circulo.h"

#include "Figura.h"
#include "FiguraCuadrada.h"
#include "FiguraCircular.h"
#include "FiguraPoligonal.h"
#include "FiguraTriangular.h"

class CargadorYaml{
public:
	
	static bool cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno);

private:

	static void cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera);
	static void cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno);
	static void cargar_figuras(const YAML::Node& listaFiguras, Terreno* terreno);
	static Dimension* obtener_dimension(const YAML::Node& dimension,const char* tipo_dimension);
	static Figura* cargarFigura(const char* tipo_figura,const char* ID,Dimension* dimension);
	static Dimension* crearDimension(const YAML::Node& dimension,double angulo,double posX,double posY, const char* tipo_dimension);
	static Dimension* crearCuadrado(const YAML::Node& dimension, double angulo,double posX,double posY);
	static Dimension* crearCirculo(const YAML::Node& dimension, double angulo,double posX,double posY);
	static void cargar_figuras_botones(const YAML::Node& listaFiguras,BotoneraController* botonera);

};