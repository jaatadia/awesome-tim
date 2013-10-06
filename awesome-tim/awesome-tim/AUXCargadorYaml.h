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
#include "Triangulo.h"
#include "PoligonoRegular.h"
#include "PelotaBasquet.h"
#include "PelotaBowling.h"
#include "GloboHelio.h"

#include "Figura.h"

class AUXCargadorYaml{
public:
	
	static bool cargarJuego(const char* file,BotoneraController* botonera,Terreno* terreno);

private:

	static std::string ruta_archivo;

	static void cargar_botones(const YAML::Node& nodoBotonera, BotoneraController* botonera);
	static void cargar_terreno(const YAML::Node& nodoTerreno,Terreno* terreno);
	static Figura* cargar_figura(const YAML::Node& nodoFig);
	static Figura* crearFigura(const YAML::Node& nodoFigura, const char* tipo_figura);

	//Funciones de validacion de datos
	static bool cant_instancias_valida(int instancias);
	static bool tipo_figura_valida(const char* tipo_figura);
	static bool posicion_validaX(double posX);
	static bool posicion_validaY(double posY);
	static bool angulo_valido(double angulo);

	static std::string concatenar_archivo(std::string mensaje, int linea, std::string archivo);
	static std::string concatenar_archivo(std::string mensaje, std::string archivo);
	static void imprimir_error_linea(std::string mensaje, int linea);
	static void imprimir_error_sin_linea(std::string mensaje);
	static void imprimir_error_excepcion(std::string mensaje,std::string what);


	static Figura* crearBalancin(const YAML::Node& nodoFigura);
	static Figura* crearCirculo(const YAML::Node& nodoFigura);
	static Figura* crearPoligono(const YAML::Node& nodoFigura);
	static Figura* crearPlataforma(const YAML::Node& nodoFigura);
	static Figura* crearCuadrado(const YAML::Node& nodoFigura);

	static void obtenerPosicion(const YAML::Node& nodoFigura, double* posX, double* posY);
	static void obtenerAngulo(const YAML::Node& nodoFigura, double* angulo);
	static void obtenerID(const YAML::Node& nodoFigura, std::string* ID);

public:

	static void pruebaCargador();

};
