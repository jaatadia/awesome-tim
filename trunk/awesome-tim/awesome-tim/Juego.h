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
#include "CreateFigureMessage.h"
#include "Boton.h"


#define JUEGO_TAG "Juego"

class Comandos;

class Juego: public Estado, Cambiable
{
private:
	std::string objetivo;
	MaquinaEstados* maq;
	const char* fileIn;
	const char* fileOut;
	Terreno* terreno;
	BotoneraController * botonera;
	Comandos* comandos;
	Figura* figuraEnAire[MAX_CLIENTES+1];
	bool estaActiva; //indica si la figura en aire esta habilitada a moverse

	bool shiftPressed;
	bool clickPressed;
	int contEventosMov;

	Figura* vector[LARGO];
	int posVector;

	std::list<int> myClients;

	int cant_jugadores;
	std::list<int> jugadoresListos;
	(std::list<struct boton>*) botoneras[MAX_CLIENTES+1];
	double areas[MAX_CLIENTES+1][4];

	bool usarVista;

public:
	Juego(const char* fileIn,const char* fileOut,MaquinaEstados* maq,bool usarVista);//se crea el juego
	~Juego(void);

	std::string cargar();
	bool guardar();

	void quit();
	void play();
	void actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento);

	bool onEvent(Ventana* ventana,Superficie** sup);//maneja los eventos
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
	void set2Click();


	void cambiarInstancias(int cliente,int tipoFigura,int cantidad);

	void reload();
};
