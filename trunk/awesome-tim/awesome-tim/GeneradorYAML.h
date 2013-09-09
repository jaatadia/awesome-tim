#pragma once
#include "yaml-cpp/yaml.h"
#include "Botonera.h"
#include "Terreno.h"
#include "Figura.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include <iostream>
#include <fstream>

class Botonera;
class Terreno;

class GeneradorYaml{

private:
	YAML::Emitter& operator << (/*YAML::Emitter& out,*/Figura* fig);

public:
	static bool guardarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	static int pruebayaml();

};