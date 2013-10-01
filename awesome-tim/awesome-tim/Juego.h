#pragma once

#include "Estado.h"

#include "Ventana.h"
#include "Superficie.h"
#include "Terreno.h"
#include "BotoneraController.h"
#include "Comandos.h"
#include "Figura.h"
#include "Cuadrado.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"
#include "MaquinaEstados.h"


#define JUEGO_TAG "Juego"

class Comandos;

class Juego: public Estado, public Fallable, Cambiable
{
private:
	
	MaquinaEstados* maq;
	const char* fileIn;
	const char* fileOut;
	Terreno* terreno;
	BotoneraController * botonera;
	Comandos* comandos;
	Figura* figuraEnAire;
	bool estaActiva; //indica si la figura en aire esta habilitada a moverse

	bool shiftPressed;

public:
	Juego(const char* fileIn,const char* fileOut,MaquinaEstados* maq);//se crea el juego
	~Juego(void);

	bool cargar();
	bool guardar();

	void quit();
	void play();
	void actuarVentana(Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento);

	void onEvent(Superficie** sup);//maneja los eventos
	void onLoop();//actualiza el modelo
	bool onRender(Superficie* superficie);//dibuja en la ventana

	void setFondo(const char* dir);

	void resume();

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
	void resizear();
};
