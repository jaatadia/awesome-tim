#pragma once

#include "Figura.h"

class Figura;

class Validable{
public:
	Validable();
	~Validable();
	void tratarFigura(Figura* figura,double x,double y);
};
