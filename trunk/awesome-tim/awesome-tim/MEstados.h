#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"
#include "MaquinaEstados.h"
#include "Message.h"
#include "MessageFigura.h"
#include "MessageState.h"

#define M_ESTADOS "Maquina de Estados"

class MEstados: public MaquinaEstados,public Fallable
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
	MEstados(const char *fileIn,const char *fileOut);
	~MEstados(void);

	bool isRunning();
	bool onEvent();
	void onLoop();
	void onRender();

	virtual void salir();
	virtual void editor();
	virtual void play(void* ter);

	//PARA RECIBIR MENSAJES
	//todos los mensajes tipo interactuar, mover, agregar figura ,etc...
	virtual void procesarMensaje(Message* msj);
	//mensaje de clase MessageState
	virtual void procesarCambioEstado(Message* msj);

	//PARA ENVIAR MENSAJES
	//devuelve todos los mensajes a enviar Y limpia la lista
//	virtual std::list<Message*> obtenerMensajes();

private:
	Estado* getEstadoActivo(){return Eactivo;}

};
