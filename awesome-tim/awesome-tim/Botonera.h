#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"

class Botonera: public Imprimible,public Validable,public Cambiable
{
private:
	int ancho,alto;
	Superficie* sup;

public:
	Botonera(int ancho,int alto);
	~Botonera(void);
	Superficie* getImpresion();
};
