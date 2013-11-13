
#pragma once
#include "Fallable.h"
#include "Estado.h"
#include "Ventana.h"
#include "MaquinaEstados.h"
#include "MessageFigura.h"
#include "MessageState.h"


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

	bool ready; //indica si esta listo para empezar a simular el juego

public:
	MEstadosCliente();
	~MEstadosCliente(void);
	void init(int id);
	bool isRunning();
	bool onEvent();
	void onLoop();
	void onRender();
	
	void esperar(double miliseconds);

	virtual void salir();
	virtual void editor();
	virtual void play(void* ter);

	//PARA RECIBIR MENSAJES
	//todos los mensajes tipo interactuar, mover, agregar figura ,etc...
	virtual void procesarMensaje(MessageFigura* msj){
	//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	//para cambiar a ready, play o stop

	virtual void procesarCambioEstado(MessageState* msj){
	//FIXME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	};

	//PARA ENVIAR MENSAJES
	//devuelve todos los mensajes a enviar Y limpia la lista
//	virtual std::list<Message*> obtenerMensajes();
private:
	Estado* getEstadoActivo(){return Eactivo;}

};
