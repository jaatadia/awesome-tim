#include "TransformFigureMessage.h"

TransformFigureMessage::TransformFigureMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_TRANSFORM_FIGURE;
	clientID = -1;
	figureID = -1;
	x = -1;
	y = -1;
	angle = -1;
	sizeChange = T_NONE;
	length = -1;
}

TransformFigureMessage::TransformFigureMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_TRANSFORM_FIGURE;
	size_t pos = msg.find("|");
	if (pos != std::string::npos){
		this->clientID = atoi(msg.substr(0, pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos){
			this->figureID = atoi(msg.substr(0, pos).c_str());
			msg = msg.substr(pos + 1);
			pos = msg.find("|");
				if (pos != std::string::npos){
				this->x = atof(msg.substr(0, pos).c_str());
				msg = msg.substr(pos + 1);
				pos = msg.find("|");
				if (pos != std::string::npos){
					this->y = atof(msg.substr(0, pos).c_str());
					msg = msg.substr(pos + 1);
					pos = msg.find("|");
					if (pos != std::string::npos){
						this->angle = atof(msg.substr(0, pos).c_str());
						msg = msg.substr(pos + 1);
						pos = msg.find("|");
						if (pos != std::string::npos){
							this->sizeChange = atoi(msg.substr(0, pos).c_str());
							msg = msg.substr(pos + 1);
							pos = msg.find("$");
							if (pos != std::string::npos){
								this->length = atoi(msg.substr(0, pos).c_str());
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


TransformFigureMessage::~TransformFigureMessage(void)
{
}

int TransformFigureMessage::getClientID(){
	return this->clientID;
}
int TransformFigureMessage::getFigureID(){
	return this->figureID;
}

double TransformFigureMessage::getX(){
	return this->x;
}

double TransformFigureMessage::getY(){
	return this->y;
}

double TransformFigureMessage::getAngle(){
	return this->angle;
}

int TransformFigureMessage::getSizeChange(){
	return this->sizeChange;
}

int TransformFigureMessage::getLength(){
	return this->length;
}

void TransformFigureMessage::setClientID(int id){
	this->clientID = id;
}
void TransformFigureMessage::setFigureID(int id){
	this->figureID = id;
}

void TransformFigureMessage::setX(double x){
	this->x = x;
}

void TransformFigureMessage::setY(double y){
	this->y = y;
}

void TransformFigureMessage::setAngle(double angle){
	this->angle = angle;
}

void TransformFigureMessage::setSizeChange(int type){
	this->sizeChange = type;
}

void TransformFigureMessage::setLength(int length){
	this->length = length;
}

string TransformFigureMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->clientID;
	ss << "|";
	ss << this->figureID;
	ss << "|";
	ss << this->x;
	ss << "|";
	ss << this->y;
	ss << "|";
	ss << this->angle;
	ss << "|";
	ss << this->sizeChange;
	ss << "|";
	ss << this->length;
	ss << "$";
	return ss.str();
}
