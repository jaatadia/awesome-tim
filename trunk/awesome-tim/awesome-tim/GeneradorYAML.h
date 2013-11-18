#pragma once

#include "Figura.h"
#include "BotoneraController.h"
#include "Terreno.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include "Triangulo.h"
#include "PoligonoRegular.h"
#include "DLinea.h"
#include "Plataforma.h"

#include <iostream>
#include <fstream>

#include "yaml-cpp/yaml.h"


class BotoneraController;
class Terreno;

class GeneradorYaml{

private:


	YAML::Emitter& operator << (Figura* fig);
	YAML::Emitter& operator << (BotoneraController* botonera);
	YAML::Emitter& operator << (Terreno* terreno);
	YAML::Emitter& operator << (Cuadrado* cuad);
	YAML::Emitter& operator << (Circulo* circ);
	YAML::Emitter& operator << (Triangulo* triang);
	YAML::Emitter& operator << (PoligonoRegular* polig);
	YAML::Emitter& operator << (DLinea* dimlinea);

public:
	static bool guardarJuego(const char* file,BotoneraController* botonera,Terreno* terreno,std::string obj);
	static int pruebayaml();

};