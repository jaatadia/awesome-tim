#pragma once

#include "Figura.h"
#include "Botonera.h"
#include "Terreno.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include "Triangulo.h"
#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"


class Botonera;
class Terreno;

class GeneradorYaml{

private:
	YAML::Emitter& operator << (Dimension* dim);

	YAML::Emitter& operator << (Figura* fig);
	YAML::Emitter& operator << (Botonera* botonera);
	YAML::Emitter& operator << (Terreno* terreno);

public:
	static bool guardarJuego(const char* file,Botonera* botonera,Terreno* terreno);
	static int pruebayaml();

};