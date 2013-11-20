#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"
#include "MaquinaEstados.h"
#include "Message.h"
#include "MessageFigura.h"
#include "MessageState.h"

#define M_ESTADOS "Maquina de Estados"

class MEstados: public MaquinaEstados
{
private:

	Estado* Eactivo;
	Estado* Eanterior;

	Estado* Eeditor;
	Estado* Eplay;

	bool running;
	
	const char* fileIn;
	const char* fileOut;
	
	Ventana* ventana;
	Superficie* superficie;

public:
	bool usarVista;
	MEstados(const char *fileIn,const char *fileOut,bool usarVista);
	~MEstados(void);

	bool isRunning();
	bool onEvent();
	bool onLoop();
	void onRender();

	virtual void salir();
	virtual void editor();
	virtual void play(void* ter);

private:
	Estado* getEstadoActivo(){return Eactivo;}

};
