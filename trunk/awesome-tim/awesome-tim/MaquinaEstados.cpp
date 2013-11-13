#include "MaquinaEstados.h"

void MaquinaEstados::pushMessage(Message * msg){
	Lock lock(this->_mutex);
	this->aEnviar.push_back(msg);
}

Message * MaquinaEstados::getNextMessage()
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