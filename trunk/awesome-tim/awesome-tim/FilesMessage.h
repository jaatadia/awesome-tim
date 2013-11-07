#ifndef __FILESMESSAGE_H__
#define __FILESMESSAGE_H__

#include "Message.h"
#include <sstream>

//TAM_BUFFER = 512
//0-1		ID Mensaje
//2-|		Nombre Archivo
//|-$		Stream

class FilesMessage : public Message
{
public:
	FilesMessage(string msg);
	virtual ~FilesMessage(void);
	virtual string serialize();
	string getNombre();
	string getStream();
private:
	string nombre;
	string stream;
};

#endif // __FILESMESSAGE_H__