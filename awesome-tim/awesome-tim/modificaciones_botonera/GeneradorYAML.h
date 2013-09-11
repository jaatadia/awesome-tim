#pragma once

#include "Figura.h"
#include "BotoneraController.h"
#include "Terreno.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"


class BotoneraController;
class Terreno;

class GeneradorYaml{

private:
	YAML::Emitter& operator << (/*YAML::Emitter& out,*/Figura* fig);

public:
	static bool guardarJuego(const char* file,BotoneraController* botonera,Terreno* terreno);
	static int pruebayaml();

};