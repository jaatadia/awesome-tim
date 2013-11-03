#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Constantes.h"

class Contenedor
{
private:
	static Contenedor* cont;

public:
	static void putMultimedia(const char* ID,void* medio);
	static void* getMultimedia(const char* ID);
	static void deleteContenedor();

	static bool estaMultimedia(const char* ID);

	static void pruebaContenedor();

private:
	
	std::map<std::string ,void*> mapa;
	
	Contenedor(void);
	~Contenedor(void);
	
};
