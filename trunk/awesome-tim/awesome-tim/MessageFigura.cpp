#include "MessageFigura.h"

//Defino cosas que no se que son: Jenny :P
#define MSG_TYPE_EVENT 0

MessageFigura::MessageFigura(string msg) : EventMessage(msg)
{
	this->type = MSG_TYPE_EVENT;
	size_t pos = msg.find("|");
	size_t posFinal = msg.find("$");
	//si no tiene final, no es valido
	if (posFinal == std::string::npos){
		this->valid = MSG_INVALID;
	}

	if (pos != std::string::npos){
		//convierto a numero
		string subTipoMsj = msg.substr(0, pos);
		stringstream ss;
		ss.str("");
		ss << subTipoMsj;
		ss >> this->subtipoMsj;
		//me quedo con el resto
		msg = msg.substr(pos + 1, posFinal + 1);
	}else{
		this->valid = MSG_INVALID;
	}

	pos = msg.find("|");
	if (pos != std::string::npos){
		//convierto a numero
		string idFig = msg.substr(0, pos);
		stringstream ss;
		ss.str("");
		ss << idFig;
		ss >> this->idFigura;
		//me quedo con el resto
		msg = msg.substr(pos + 1, posFinal + 1);
	}else{
		this->valid = MSG_INVALID;
	}

	pos = msg.find("|");
	if (pos != std::string::npos){
		this->data1 = msg.substr(0, pos);
		msg = msg.substr(pos + 1, posFinal + 1);
	}else{
		this->valid = MSG_INVALID;
	}

	pos = msg.find("|");
	if (pos != std::string::npos){
		this->data2 = msg.substr(0, pos);
		msg = msg.substr(pos + 1, posFinal + 1);
	}else{
		this->valid = MSG_INVALID;
	}

	pos = msg.find("$");
	if (pos != std::string::npos){
		this->data3 = msg.substr(0, pos);
		msg = msg.substr(pos + 1, posFinal + 1);
	}else{
		this->valid = MSG_INVALID;
	}

	//solo debería haber quedado adentro el signo de pesos
	if (msg.length() > 1){
		this->valid = MSG_INVALID;
	}

}

MessageFigura::~MessageFigura(void)
{
}

string MessageFigura::serialize()
{
	//el string a devolver
	string retorno;

	//guardo el tipo de mensaje
	stringstream ss;
	ss << this->type;
	string tipoMsj;
	tipoMsj = ss.str();
	retorno.append(tipoMsj).append("|");
	
	//guardo los 4 campos
	ss.str("");
	ss << subtipoMsj;
	string subTipo;
	subTipo = ss.str();
	retorno.append(subTipo).append("|");

	ss.str("");
	ss << idFigura;
	string id;
	id = ss.str();
	retorno.append(id).append("|");

	retorno.append(data1).append("|");
	
	retorno.append(data2).append("|");

	retorno.append(data3).append("$");

	return retorno;
}

int MessageFigura::getSubtipoMsj()
{
	return subtipoMsj;
}

int MessageFigura::getIdFigura()
{
	return idFigura;
}

string MessageFigura::getData1()
{
	return data1;
}

string MessageFigura::getData2()
{
	return data2;
}

string MessageFigura::getData3()
{
	return data3;
}
