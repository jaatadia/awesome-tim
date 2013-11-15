#pragma once
#include <list>
#include "Message.h"
#include "Mutex.h"
#include "Lock.h"

class Terrreno;

class MaquinaEstados
{
public:
	


	std::list<Message *> aEnviar[MAX_CLIENTES+1];
	std::list<Message *> aProcesar;
	void pushSendMessage(Message * msg, int id = -1);
	void pushProcessMessage(Message * msg);
	Message * getSendMessage(int id);
	Message * getProcessMessage();

	int getNextClient();
	void setMaxClients(int clients);
	void addClient(int id);
	void removeClient(int id);

	void setId(int id);
	int getId();
	static void putMensaje(int tipo,int nroFigura,int data1,int data2);
	MaquinaEstados();
	virtual ~MaquinaEstados();
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
	int id;
	std::list<int> clientesConectados;
	int clientesDelJuego;
};