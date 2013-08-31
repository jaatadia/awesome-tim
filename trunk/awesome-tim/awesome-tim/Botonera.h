#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"

class Botonera: public Imprimible,Validable,Cambiable
{
private:
	Imagen* img;

public:
	Botonera(void);
	void setFondo(Imagen* img);
	~Botonera(void);
};
