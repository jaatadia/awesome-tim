#pragma once

#include "Imprimible.h"
#include "Cambiable.h"

class Comandos: public Imprimible,public Cambiable
{
private:
	int ancho,alto;
	Superficie* sup;

public:
	Comandos(int ancho,int alto);
	~Comandos(void);
	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes* escalas);
};
