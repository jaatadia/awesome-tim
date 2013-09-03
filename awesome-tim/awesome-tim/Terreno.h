#pragma once

#include "Imprimible.h"
#include "Validable.h"
#include "Cambiable.h"

class Terreno: public Imprimible,public Validable,public Cambiable
{
private:
	int ancho,alto;
	Imagen* img;
	Superficie* sup;

public:
	Terreno(int ancho,int alto);
	~Terreno(void);
	void setFondo(Imagen* img);
	Superficie* getImpresion();

};
