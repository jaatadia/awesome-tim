
#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"
#include "MaquinaEstados.h"


#define M_ESTADOS "Maquina de Estados"

class MEstadosCliente: public MaquinaEstados,public Fallable
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
	int id;

public:
	MEstadosCliente();
	~MEstadosCliente(void);

	bool isRunning();
	bool onEvent();
	void onLoop();
	void onRender();
	
	void esperar(double miliseconds);
	void setId(int id);
	void init();


	virtual void salir();
	virtual void editor();
	virtual void play(void* ter);

private:
	Estado* getEstadoActivo(){return Eactivo;}

};
