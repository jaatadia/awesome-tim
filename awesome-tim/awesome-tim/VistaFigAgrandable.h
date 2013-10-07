#pragma once
#include "vistafigura.h"

class VistaFigAgrandable :	public VistaFigura
{
private:
	double largo_anterior;
	Imagen* imggrande;

public:
	VistaFigAgrandable(Figura* fig);
	~VistaFigAgrandable(void);
protected:
	virtual void redraw();
};
