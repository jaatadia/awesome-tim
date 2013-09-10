#pragma once
#include <iostream>
#include <map>
#include <string>

class Contenedor
{
private:
	static Contenedor* cont;
public:
	static void putMultimedia(const char* ID,void* medio);
	static void* getMultimedia(const char* ID);
	static void deleteContenedor();

	static void pruebaContenedor();

private:
	
	std::map<const char* ,void*> mapa;
	
	Contenedor(void);
	~Contenedor(void);
	
};
