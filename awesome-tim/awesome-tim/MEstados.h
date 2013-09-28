#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"

#define M_ESTADOS "Maquina de Estados"

class MEstados: public Fallable
{
private:

	Estado* activo;

	Estado* editor;
	Estado* play;

	bool running;
	const char* fileIn;
	const char* fileOut;
	
	Ventana* ventana;
	Superficie* superficie;

public:
	MEstados(const char *fileIn,const char *fileOut);
	~MEstados(void);

	bool isRunning();
	void onEvent();
	void onLoop();
	void onRender();
	
	void esperar(double miliseconds);

private:
	Estado* getEstadoActivo(){return activo;}

};
