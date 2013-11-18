#include "InteractMessage.h"

InteractMessage::InteractMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_INTERACT;
}

InteractMessage::InteractMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_INTERACT;
	size_t pos = msg.find("|");
	if(pos != std::string::npos){
		this->figureID = atoi(msg.substr(0,pos).c_str());
		msg = msg.substr(pos+1);
		pos = msg.find("$");
		if(pos != std::string::npos){
			this->action = atoi(msg.substr(0,pos).c_str());
		}else{
			this->valid = MSG_INVALID;
		}
	}else{
		this->valid = MSG_INVALID;
	}
}

InteractMessage::~InteractMessage(void)
{
}

string InteractMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->figureID;
	ss << "|";
	ss << this->action;
	ss << "$";
	return ss.str();
}

void InteractMessage::setFigureID(int id){
	this->figureID = id;
}
int InteractMessage::getFigureID(){
	return this->figureID;
}
void InteractMessage::setAction(int id){
	this->action = id;
}
int InteractMessage::getAction(){
	return this->action;
}