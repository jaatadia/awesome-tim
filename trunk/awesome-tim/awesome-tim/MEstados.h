#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"
#include "MaquinaEstados.h"

#define M_ESTADOS "Maquina de Estados"

class MEstados: public MaquinaEstados,public Fallable
{
private:

	Estado* Eactivo;

	Estado* Eeditor;
	Estado* Eplay;

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


	virtual void salir();
	virtual void editor();
	virtual void play(Terreno* ter);

private:
	Estado* getEstadoActivo(){return Eactivo;}

};