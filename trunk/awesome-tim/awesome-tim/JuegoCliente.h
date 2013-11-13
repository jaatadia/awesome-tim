#pragma once

#include "Estado.h"

#include "Ventana.h"
#include "Superficie.h"
#include "TerrenoCliente.h"
#include "BotoneraControllerCliente.h"
#include "ComandosCliente.h"
#include "Figura.h"
#include "Cuadrado.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"
#include "MaquinaEstados.h"
#include "MouseMotionMessage.h"
#include "CreateFigureMessage.h"
#include "MessageFigura.h"


#define JUEGO_TAG "Juego"


class ComandosCliente;

class JuegoCliente: public Estado, Cambiable
{
private:
	
	MaquinaEstados* maq;
	const char* fileIn;
	const char* fileOut;
	TerrenoCliente* terreno;
	BotoneraControllerCliente * botonera;
	ComandosCliente* comandos;
	
	Figura* figurasEnAire[MAX_CLIENTES+1];
	
	bool estaActiva; //indica si la figura en aire esta habilitada a moverse

	bool shiftPressed;
	bool clickPressed;
	int contEventosMov;

	Figura* vector[LARGO];
	int posVector;
	int numCliente;

public:
	JuegoCliente(int nroCliente,MaquinaEstados* maq);//se crea el juego
	~JuegoCliente(void);

	bool cargar();
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
	void procesarActualizaciones();
	void procesarMensaje(MessageFigura* msj);

};
