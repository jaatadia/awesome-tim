#include "CreateFigureMessage.h"

CreateFigureMessage::CreateFigureMessage(void)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_CREATE_FIGURE;
	this->id = 0;
	this->figureType = 0;
	this->x = 0;
	this->y = 0;
	this->angle = 0;
	this->inAir = false;
	this->figureType = -1;
	this->data1 = 0;
	this->data2 = 0;

}

CreateFigureMessage::~CreateFigureMessage(void)
{
}

CreateFigureMessage::CreateFigureMessage(string msg)
{
	this->valid = MSG_VALID;
	this->type = MSG_TYPE_CREATE_FIGURE;
	size_t pos = msg.find("|");
	if (pos != std::string::npos)
	{
		this->id = atoi(msg.substr(0, pos).c_str());
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos)
		{
			this->figureType = atoi(msg.substr(0, pos).c_str());
			msg = msg.substr(pos + 1);
			pos = msg.find("|");
			if (pos != std::string::npos)
			{
				this->figureID = atoi(msg.substr(0, pos).c_str());
				msg = msg.substr(pos + 1);
				pos = msg.find("|");
				if (pos != std::string::npos)
				{
					this->x = atof(msg.substr(0, pos).c_str());
					msg = msg.substr(pos + 1);
					pos = msg.find("|");
					if (pos != std::string::npos)
					{
						this->y = atof(msg.substr(0, pos).c_str());
						msg = msg.substr(pos + 1);
						pos = msg.find("|");
						if (pos != std::string::npos)
						{
							this->angle = atof(msg.substr(0, pos).c_str());
							msg = msg.substr(pos + 1);
							pos = msg.find("|");
							if (pos != std::string::npos)
							{
								this->inAir = (msg.substr(0, pos).compare("T") == 0) ? true : false;
								msg = msg.substr(pos + 1);
								pos = msg.find("|");
								if (pos != std::string::npos){
									this->data1 = atof(msg.substr(0, pos).c_str());
									msg = msg.substr(pos + 1);
									pos = msg.find("$");
									if (pos != std::string::npos){
										this->data2 = atof(msg.substr(0, pos).c_str());
									}else{
										this->valid = MSG_INVALID;
									}
								}else{
									this->valid = MSG_INVALID;
								}
							}
							else
							{
								this->valid = MSG_INVALID;
							}
						}
						else
						{
							this->valid = MSG_INVALID;
						}
					}
					else
					{
						this->valid = MSG_INVALID;
					}
				}
				else
				{
					this->valid = MSG_INVALID;
				}
			}
			else
			{
				this->valid = MSG_INVALID;
			}
		}
		else
		{
			this->valid = MSG_INVALID;
		}
	}
	else
	{
		this->valid = MSG_INVALID;
	}
}

int CreateFigureMessage::getId()
{
	return this->id;
}

int CreateFigureMessage::getFigureType()
{
	return this->figureType;
}

int CreateFigureMessage::getFigureID(){
	return this->figureID;
}

double CreateFigureMessage::getX()
{
	return this->x;
}

double CreateFigureMessage::getY()
{
	return this->y;
}

double CreateFigureMessage::getAngle()
{
	return this->angle;
}

bool CreateFigureMessage::isInAir()
{
	return this->inAir;
}

double CreateFigureMessage::getData1()
{
	return this->data1;
}

double CreateFigureMessage::getData2()
{
	return this->data2;
}

void CreateFigureMessage::setId(int id)
{
	this->id = id;
}

void CreateFigureMessage::setFigureType(int figureType)
{
	this->figureType = figureType;
}

void CreateFigureMessage::setFigureID(int figureID){
	this->figureID = figureID;
}

void CreateFigureMessage::setX(double x)
{
	this->x = x;
}

void CreateFigureMessage::setY(double y)
{
	this->y = y;
}

void CreateFigureMessage::setAngle(double angle)
{
	this->angle = angle;
}

void CreateFigureMessage::setInAir(bool inAir)
{
	this->inAir = inAir;
}

void CreateFigureMessage::setData1(double data1)
{
	this->data1 = data1;
}

void CreateFigureMessage::setData2(double data2)
{
	this->data2 = data2;
}


string CreateFigureMessage::serialize()
{
	stringstream ss;
	ss << this->type;
	ss << "|";
	ss << this->id;
	ss << "|";
	ss << this->figureType;
	ss << "|";
	ss << this->figureID;
	ss << "|";
	ss << this->x;
	ss << "|";
	ss << this->y;
	ss << "|";
	ss << this->angle;
	ss << "|";
	ss << ((this->inAir) ? "T" : "F");
	ss << "|";
	ss << this->data1;
	ss << "|";
	ss << this->data2;
	ss << "$";
	return ss.str();
}