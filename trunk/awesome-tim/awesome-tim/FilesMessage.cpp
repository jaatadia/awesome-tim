#include "FilesMessage.h"

FilesMessage::FilesMessage(string msg)
{
	this->type = MSG_TYPE_FILES;
	size_t pos = msg.find("|");
	if (pos != std::string::npos)
	{
		this->nombre = msg.substr(0, pos);
		msg = msg.substr(pos + 1);
		pos = msg.find("$");
		if (pos != std::string::npos)
		{
			this->stream = msg.substr(0, pos);
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

FilesMessage::~FilesMessage()
{

}

string FilesMessage::serialize()
{
	stringstream ss;
	ss << this->type;
	string retorno = ss.str();
	retorno.append("|").append(this->nombre).append("|").append(this->stream).append("$");
	return retorno;
}

string FilesMessage::getNombre()
{
	return this->nombre;
}

string FilesMessage::getStream()
{
	return this->stream;
}