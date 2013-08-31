#pragma once

#include "Ventana.h"
#include "Superficie.h"
#include "Terreno.h"
#include "Botonera.h"
#include "Comandos.h"
#include "Figura.h"

#define JUEGO_TAG "Juego"

class Juego: public Fallable
{
private:
	bool running;
	const char* file;
	Ventana* ventana;
	Superficie* superficie;
	Terreno* terreno;
	Botonera* botones;
	Comandos* comandos;
	Figura* figuraEnAire;
	
public:
	Juego(const char* file);//se crea el juego
	~Juego(void);
	bool correr();//ejecuta el juego, devualve false si hubo error
	bool cargar();
	bool guardar();

private:
	void onEvent();//maneja los eventos
	void onLoop();//actualiza el modelo
	void onRender();//dibuja en la ventana
};
