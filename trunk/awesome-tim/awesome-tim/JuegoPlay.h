#pragma once
#include "Superficie.h"
#include "Ventana.h"
#include "Terreno.h"
#include "Estado.h"
#include "MaquinaEstados.h"
#include "ComandosPlay.h"

class ComandosPlay;

class JuegoPlay: public Estado, public Cambiable
{
private:
	MaquinaEstados* maq;
	ComandosPlay* comandos;
	Terreno* terreno;
	Superficie* fondo;
	bool dibujar;
	int contador;
	
	//cosas para dibujar que gano
	bool gano;
	int contadorGano;
	Imagen* imgGano;


public:
	JuegoPlay(Superficie* fondo,void* ter,MaquinaEstados* maq);
	~JuegoPlay(void);

	virtual bool onEvent(Ventana* ventana,Superficie** sup);
	virtual void onLoop();
	virtual bool onRender(Superficie* sup);
	
	void quit();

private:
	void actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento);

	void actualizarVictoria();
	void dibujarVictoria(Superficie* sup);
};
