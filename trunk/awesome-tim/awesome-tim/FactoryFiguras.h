#pragma once

#include "Figura.h"
#include "CreateFigureMessage.h"

class FactoryFiguras
{
public:

	static Figura* create(CreateFigureMessage* msg);

};
