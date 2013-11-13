#include "MessageState.h"

//Defino cosas que no se que son: Jenny :P
#define MSG_TYPE_CHANGE_STATE 0

MessageState::MessageState(string msg)
{
	this->type = MSG_TYPE_CHANGE_STATE;

	//solo tiene un campo
	size_t pos = msg.find("$");
	if (pos != std::string::npos){
		//convierto a numero
		string estadoStr = msg.substr(0, pos);
		stringstream ss;
		ss.str("");
		ss << estadoStr;
		ss >> this->estado;
	}else{
		this->valid = MSG_INVALID;
	}
}

MessageState::~MessageState(void)
{
}

string MessageState::serialize(){

	stringstream ss;
	ss << this->type;
	string retorno = ss.str();
	retorno.append("|");

	ss.str("");
	ss << this->estado;
	retorno.append(ss.str()).append("$");

	return retorno;
}

int MessageState::getEstado(){

	return estado;
}