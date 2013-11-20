#pragma once

#pragma once
#include "Superficie.h"
#include "Ventana.h"
#include "Estado.h"
#include "MaquinaEstados.h"
#include "MessageFigura.h"

#include "ComandosPlayCliente.h"
#include "TerrenoCliente.h"

class ComandosPlayCliente;

class JuegoPlayCliente: public Estado, public Cambiable
{
private:
	MaquinaEstados* maq;
	ComandosPlayCliente* comandos;
	TerrenoCliente* terreno;
	Superficie* fondo;
	
	//cosas para dibujar que gano
	bool gano;
	int contadorGano;
	Imagen* imgGano;


	Figura* vector[LARGO];
	int posVector;
	int numCliente;
	int contador;

public:
	JuegoPlayCliente(Superficie* fondo,void* ter,MaquinaEstados* maq);
	~JuegoPlayCliente(void);

	virtual bool onEvent(Ventana* ventana,Superficie** sup);
	virtual bool onLoop();
	virtual bool onRender(Superficie* sup);
	
	void quit();

	//si ya esta en play no hace nada
	void cambiarAPlay(){};

	void procesarMensaje(MessageFigura* msj);

	void sendUnready();

private:
	void actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento);

	void actualizarVictoria();
	void dibujarVictoria(Superficie* sup);

};
