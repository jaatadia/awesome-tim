#pragma once
#include <list>
#include "Message.h"
#include "Mutex.h"
#include "Lock.h"

class Terrreno;

class MaquinaEstados
{
public:
	std::list<Message *> aEnviar;
	std::list<Message *> aProcesar;
	void pushMessage(Message * msg);
	Message * getNextMessage();
	static void putMensaje(int tipo,int nroFigura,int data1,int data2);
	virtual ~MaquinaEstados(){};
	virtual void salir()=0;
	virtual void editor()=0;
	virtual void play(void* ter)=0;

	virtual bool isRunning()=0;
	virtual bool onEvent()=0;
	virtual void onLoop()=0;
	virtual void onRender()=0;
	virtual void esperar(double tiempo)=0;

private:
	Mutex _mutex;
};