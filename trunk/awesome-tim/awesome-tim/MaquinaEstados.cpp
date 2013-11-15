#include "MaquinaEstados.h"
MaquinaEstados::MaquinaEstados(){
	clientesDelJuego = MAX_CLIENTES;
}

MaquinaEstados::~MaquinaEstados(){
}

void MaquinaEstados::pushSendMessage(Message * msg, int id){
	Lock lock(this->_mutex);
	if(id < 0)
	{
		for (int i = 1; i <= MAX_CLIENTES; i++)
		{
			this->aEnviar[i].push_back(msg);
		}
	}
	else
	{
		this->aEnviar[id].push_back(msg);
	}
}

Message * MaquinaEstados::getSendMessage(int id)
{
	if(id==-1) return NULL;

	Lock lock(this->_mutex);
	Message * msg = NULL;
	if(!this->aEnviar[id].empty())
	{
		msg = (Message *) this->aEnviar[id].front();
		this->aEnviar[id].pop_front();
	}
	return msg;
}

Message * MaquinaEstados::getProcessMessage()
{
	Lock lock(this->_mutex);
	Message * msg = NULL;
	if(!this->aProcesar.empty())
	{
		msg = (Message *) this->aProcesar.front();
		this->aProcesar.pop_front();
	}
	return msg;
}

void MaquinaEstados::addClient(int id){
	Lock lock(this->_mutex);
	this->clientesConectados.push_back(id);
}

void MaquinaEstados::removeClient(int id){
	Lock lock(this->_mutex);
	this->aEnviar[id].clear();
	this->clientesConectados.remove(id);
}

void MaquinaEstados::setMaxClients(int clients){
	Lock lock(this->_mutex);
	this->clientesDelJuego = ((clients>0)&&(clients<=clientesDelJuego)) ? clients : clientesDelJuego;
}

int MaquinaEstados::getNextClient(){
	Lock lock(this->_mutex);
	
	if (this->clientesConectados.size()==this->clientesDelJuego) return -1;

	std::list<int> aux;
	std::list<int>::iterator iter;
	for(int i=1;i<=this->clientesDelJuego;i++) aux.push_back(i);
	for(iter = this->clientesConectados.begin();iter != this->clientesConectados.end();iter++) aux.remove(*iter);
	
	return aux.front();
}

void MaquinaEstados::pushProcessMessage(Message * msg)
{
	Lock lock(this->_mutex);
	this->aProcesar.push_back(msg);
}

void MaquinaEstados::returnProcessMessage(Message * msg){
	Lock lock(this->_mutex);
	this->aProcesar.push_front(msg);
}

void MaquinaEstados::putMensaje(int tipo, int nroFigura, int data1, int data2){
	std::cout<<"Tipo: "<<tipo<<" Cliente Nro: "<<-1<<" Numero Fig: "<<nroFigura<<" Data: "<<data1<<data2<<"\n";
}

void MaquinaEstados::setId(int id)
{
	Lock lock(this->_mutex);
	this->id = id;
}

int MaquinaEstados::getId()
{
	Lock lock(this->_mutex);
	return this->id;
}