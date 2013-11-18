#include "FireBowMessage.h"

FireBowMessage::FireBowMessage(void)
{
	this->type = MSG_TYPE_FIRE_BOW;
	this->valid = MSG_VALID;
}

FireBowMessage::FireBowMessage(string msg)
{
	this->type = MSG_TYPE_FIRE_BOW;
	this->valid = MSG_VALID;
	size_t pos = msg.find("|");
	if(pos != std::string::npos){
		this->gunID = atoi(msg.substr(0,pos).c_str());
		msg = msg.substr(pos+1);
		pos = msg.find("$");
		if(pos != std::string::npos){
			this->proyectileID = atoi(msg.substr(0,pos).c_str());
		}else{
			this->valid = MSG_INVALID;
		}
	}else{
		this->valid = MSG_INVALID;
	}
}

FireBowMessage::~FireBowMessage(void)
{
}

string FireBowMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->gunID;
	ss << "|";
	ss << this->proyectileID;
	ss << "$";

	return ss.str();
}

void FireBowMessage::setGunID(int id){
	this->gunID = id;
}
void FireBowMessage::setProyectileID(int id){
	this->proyectileID = id;
}

int FireBowMessage::getGunID(){
	return this->gunID;
}
int FireBowMessage::getProyectileID(){
	return this->proyectileID;
}