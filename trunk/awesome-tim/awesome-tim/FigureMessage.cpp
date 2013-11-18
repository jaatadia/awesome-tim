#include "FigureMessage.h"

FigureMessage::FigureMessage(void)
{
	this->valid = MSG_VALID;
}

FigureMessage::FigureMessage(string msg)
{
	this->valid = MSG_VALID;
	size_t pos = msg.find("$");
	if (pos != std::string::npos){
		this->figureID = atoi(msg.substr(0, pos).c_str());
	}else{
		this->valid = MSG_INVALID;
	}

}

FigureMessage::~FigureMessage(void)
{
}

string FigureMessage::serialize(){
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->figureID;
	ss << "$";
	return ss.str();
}

void FigureMessage::setFigureID(int figureID){
	this->figureID = figureID;
}

int FigureMessage::getFigureID(){
	return this->figureID;
}