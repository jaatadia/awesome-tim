#include "UnionMessage.h"

UnionMessage::UnionMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_UNION1;
}

UnionMessage::UnionMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_UNION1;
	size_t pos = msg.find("|");
	if (pos != std::string::npos){
		this->clientID = atoi(msg.substr(0, pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos){
			this->numFig = atoi(msg.substr(0, pos).c_str());
			msg = msg.substr(pos + 1);
			pos = msg.find("|");
			if (pos != std::string::npos){
				this->x = atof(msg.substr(0, pos).c_str());
				msg = msg.substr(pos + 1);
				pos = msg.find("$");
				if (pos != std::string::npos){
					this->y = atof(msg.substr(0, pos).c_str());
				}else{
					this->valid = MSG_INVALID;
				}
			}else{
				this->valid = MSG_INVALID;
			}
		}else{
			this->valid = MSG_INVALID;
		}
	}else{
		this->valid = MSG_INVALID;
	}
}

UnionMessage::~UnionMessage(void)
{
}

void UnionMessage::setClientID(int id){
	this->clientID = id;
}

int UnionMessage::getClientID(){
	return this->clientID;
}
void UnionMessage::setFigsNum(int numFig, double x, double y){
	this->numFig = numFig;
	this->x = x;
	this->y = y;
}

void UnionMessage::getFigsNum(int* numFig, double* x, double* y){
	*numFig = this->numFig;
	*x = this->x;
	*y = this->y;
}

string UnionMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->clientID;
	ss << "|";
	ss << this->numFig;
	ss << "|";
	ss << this->x;
	ss << "|";
	ss << this->y;
	ss << "$";
	return ss.str();
}