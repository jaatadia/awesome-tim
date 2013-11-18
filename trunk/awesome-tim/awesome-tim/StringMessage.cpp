#include "StringMessage.h"

StringMessage::StringMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_STRING;
}

StringMessage::StringMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_STRING;

	size_t pos = msg.find("$");
	if (pos != std::string::npos){
		this->cadena = msg.substr(0,pos);
	}else{
		this->valid = MSG_INVALID;
	}
}

StringMessage::~StringMessage(void)
{
}

void StringMessage::setString(string cadena){
	this->cadena = cadena.c_str();
}

string StringMessage::getString(){
	return cadena.c_str();
}
string StringMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << cadena;
	ss << "$";
	
	return ss.str();
}