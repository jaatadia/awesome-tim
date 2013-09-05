#pragma once

class Contenedor
{
public:
	static void putMultimedia(char* ID,void* medio);
	static void* getMultimedia(char* ID);
	static void deleteContenedor();

private:
	Contenedor(void);
	~Contenedor(void);
	void put(char* ID,void* medio);
	void* get(char* ID);

};
