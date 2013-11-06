#include "FilesMessage.h"

FilesMessage::FilesMessage(string msg)
{
	this->type = MSG_TYPE_FILES;
	size_t pos = msg.find("|");
	if (pos != std::string::npos)
	{
		this->nombre = msg.substr(0, pos);
		msg = msg.substr(pos + 1);
		pos = msg.find("|");
		if (pos != std::string::npos)
		{
			this->stream = msg.substr(0, pos);
		}
		else this->stream = msg;
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
	string retorno = this->type + "";
	retorno.append(this->nombre).append(this->stream);
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