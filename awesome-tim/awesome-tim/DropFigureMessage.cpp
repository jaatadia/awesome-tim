#include "DropFigureMessage.h"

DropFigureMessage::DropFigureMessage(void)
{
	this->type = MSG_TYPE_DROP;
	this->type = MSG_VALID;
}

DropFigureMessage::DropFigureMessage(string msg)
{
	this->type = MSG_TYPE_DROP;
	this->valid = MSG_VALID;
	size_t pos = msg.find("|");
	if(pos != std::string::npos){
		this->clientID = atoi(msg.substr(0,pos).c_str());
		msg = msg.substr(pos+1);
		pos = msg.find("$");
		if(pos != std::string::npos){
			this->figureID = atoi(msg.substr(0,pos).c_str());
		}else{
			this->valid = MSG_INVALID;
		}
	}else{
		this->valid = MSG_INVALID;
	}
}

DropFigureMessage::~DropFigureMessage(void)
{
}


string DropFigureMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->clientID;
	ss << "|";
	ss << this->figureID;
	ss << "$";

	return ss.str();
}
void DropFigureMessage::setClientID(int id){
	this->clientID = id;
}
int DropFigureMessage::getClientID(){
	return this->clientID;
}
void DropFigureMessage::setFigureID(int id){
	this->figureID = id;
}
int DropFigureMessage::getFigureID(){
	return this->figureID;
}