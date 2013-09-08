#pragma once

#include "Ventana.h"
#include "Superficie.h"
#include "Terreno.h"
#include "Botonera.h"
#include "Comandos.h"
#include "Figura.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"

#define JUEGO_TAG "Juego"

class Juego: public Fallable
{
private:
	
	bool running;
	const char* file;
	
	Ventana* ventana;
	Superficie* superficie;
	Terreno* terreno;
	Botonera* botonera;
	Comandos* comandos;
	Figura* figuraEnAire;

	EscalasDeEjes* escalas;

	bool shiftPressed;

public:
	Juego(const char* file);//se crea el juego
	~Juego(void);
	bool isRunning();

	bool cargar();
	bool guardar();

	void quit();
	void actuarVentana(Uint32 IDventana,SDL_WindowEvent evento,EscalasDeEjes* escalas);

	void onEvent();//maneja los eventos
	void onLoop();//actualiza el modelo
	void onRender();//dibuja en la ventana
};
