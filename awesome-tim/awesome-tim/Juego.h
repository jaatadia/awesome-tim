#pragma once

#include "Ventana.h"
#include "Superficie.h"
#include "Terreno.h"
#include "BotoneraController.h"
#include "Comandos.h"
#include "Figura.h"
#include "Cuadrado.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"

#define JUEGO_TAG "Juego"

class Comandos;

class Juego: public Fallable, Cambiable
{
private:
	
	bool running;
	const char* file;
	
	Ventana* ventana;
	Superficie* superficie;
	Terreno* terreno;
	BotoneraController * botonera;
	Comandos* comandos;
	Figura* figuraEnAire;
	bool estaActiva; //indica si la figura en aire esta habilitada a moverse

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

	void setFondo(const char* dir);

private:
	bool posEnTerreno(double posX,double posY);
	bool posEnBotonera(double posX,double posY);
	bool posEnComandos(double posX,double posY);
	void soltarFiguraEnAire();
	void confirmarPosicionFiguraEnAire();
	bool figEnEspacioIntermedio();
	bool figEnTerreno();
	bool figEnBotonera();
	bool figEnComandos();
};
