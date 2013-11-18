#include "RotateMessage.h"

RotateMessage::RotateMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_ROTATE;
}

RotateMessage::RotateMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_ROTATE;
	size_t pos = msg.find("|");
	if(pos != std::string::npos){
		this->figureID = atoi(msg.substr(0,pos).c_str());
		msg = msg.substr(pos+1);
		pos = msg.find("$");
		if(pos != std::string::npos){
			this->angle = atof(msg.substr(0,pos).c_str());
		}else{
			this->type = MSG_INVALID;
		}
	}else{
		this->type = MSG_INVALID;
	}
}

RotateMessage::~RotateMessage(void)
{
}

string RotateMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->figureID;
	ss << "|";
	ss << this->angle;
	ss << "$";
	return ss.str();
}

int RotateMessage::getFigureID(){
	return this->figureID;
}
double RotateMessage::getAngle(){
	return this->angle;
}

void RotateMessage::setFigureID(int ID){
	this->figureID = ID;
}
void RotateMessage::setAngle(double angle){
	this->angle = angle;
}