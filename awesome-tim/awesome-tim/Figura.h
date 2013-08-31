#pragma once

#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "Cambiable.h"

class Figura: public Dibujable,Cambiable
{
private:
	Dimension* dimension;
	Posicion pos;
	double angulo;

public:
	Figura(void);
	~Figura(void);
	Dimension* getDimension(){return dimension;}
};
