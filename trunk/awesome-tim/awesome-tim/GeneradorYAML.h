#pragma once
#include "yaml-cpp/yaml.h"
#include "Botonera.h"
#include "Terreno.h"
#include "Figura.h"

class Botonera;
class Terreno;

class GeneradorYaml{

private:
	YAML::Emitter& operator << (/*YAML::Emitter& out,*/Figura* fig);

public:
	static bool guardarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	static int pruebayaml();

};