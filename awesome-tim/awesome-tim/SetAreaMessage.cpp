#include "SetAreaMessage.h"

SetAreaMessage::SetAreaMessage(void)
{
	this->type = MSG_TYPE_SET_AREA;
	this->valid = MSG_VALID;
}

SetAreaMessage::SetAreaMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_SET_AREA;
	size_t pos = msg.find("|");
	if (pos != std::string::npos){
		this->x1 = atof(msg.substr(0,pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos){
			this->y1 = atof(msg.substr(0,pos).c_str());
			msg = msg.substr(pos + 1);
			pos = msg.find("|");
			if (pos != std::string::npos){
				this->x2 = atof(msg.substr(0,pos).c_str());
				msg = msg.substr(pos + 1);
				pos = msg.find("$");
				if (pos != std::string::npos){
					this->y2 = atof(msg.substr(0,pos).c_str());
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

SetAreaMessage::~SetAreaMessage(void)
{
}

void SetAreaMessage::setPuntos(double x1,double y1,double x2,double y2){
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void SetAreaMessage::getPuntos(double* x1,double* y1,double* x2,double* y2){
	*x1 = this->x1;
	*y1 = this->y1;
	*x2 = this->x2;
	*y2 = this->y2;
}

string SetAreaMessage::serialize(){
		stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->x1;
	ss << "|";
	ss << this->y1;
	ss << "|";
	ss << this->x2;
	ss << "|";
	ss << this->y2;
	ss << "$";
	return ss.str();
}