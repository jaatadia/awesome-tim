#pragma once

#include "Figura.h"
#include "BotoneraController.h"
#include "Terreno.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include "Triangulo.h"
#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"


class BotoneraController;
class Terreno;

class GeneradorYaml{

private:
	YAML::Emitter& operator << (Dimension* dim);

	YAML::Emitter& operator << (Figura* fig);
	YAML::Emitter& operator << (BotoneraController* botonera);
	YAML::Emitter& operator << (Terreno* terreno);

public:
	static bool guardarJuego(const char* file,BotoneraController* botonera,Terreno* terreno);
	static int pruebayaml();

};