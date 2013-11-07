#pragma once
#include "figura.h"

class PaletaFlipper :
	public Figura
{

public:
	PaletaFlipper(void);
	~PaletaFlipper(void);

	virtual void interactuar(int accion);
};
