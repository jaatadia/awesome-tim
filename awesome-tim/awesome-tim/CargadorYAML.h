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

	//Funciones de validacion de datos
	static bool cant_instancias_valida(int instancias);
	static bool tipo_figura_botonera_valida(int tipo_figura);
	static bool fondo_terreno_valido(const char* fondo);
	static bool tipo_dimension_valida(const char* tipo_dimension);
	static bool radio_valido(double radio);
	static bool alto_cuadrado_valido(double alto);
	static bool ancho_cuadrado_valido(double alto);
	static bool posicion_validaX(double posX);
	static bool posicion_validaY(double posY);
	static bool angulo_valido(double angulo);
	static bool tipo_figura_valida(const char* tipo_figura);

	static void imprimir_error_linea(std::string mensaje, int linea);

};
