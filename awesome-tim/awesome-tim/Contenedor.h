#pragma once
#include <iostream>
#include <map>
#include <string>

class Contenedor
{
private:
	static Contenedor* cont;
public:
	static void putMultimedia(char* ID,void* medio);
	static void* getMultimedia(char* ID);
	static void deleteContenedor();

private:
	
	std::map<char* ,void*> mapa;
	
	Contenedor(void);
	~Contenedor(void);
	void put(char* ID,void* medio);
	void* get(char* ID);

};
