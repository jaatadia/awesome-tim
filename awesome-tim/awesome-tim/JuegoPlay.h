#pragma once
#include "Superficie.h"
#include "Terreno.h"
#include "Estado.h"
#include "MaquinaEstados.h"

class JuegoPlay: public Estado, public Fallable, Cambiable
{
private:
	MaquinaEstados* maq;
	Terreno* terreno;
public:
	JuegoPlay(Terreno* ter,MaquinaEstados* maq);
	~JuegoPlay(void);

	virtual void onEvent(Superficie** sup);
	virtual void onLoop();
	virtual bool onRender(Superficie* sup);

private:
	void actuarVentana(Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento);
};
