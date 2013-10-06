#pragma once
#include "vistafigura.h"

class VistaFigAgrandable :	public VistaFigura
{
public:
	VistaFigAgrandable(Figura* fig);
	~VistaFigAgrandable(void);
	virtual void redraw();
	//dibuja la figura tomando su posicion como pixels
	virtual void dibujarEnPixel(Superficie* canvas);
	virtual void dibujar(Superficie* canvas,int xIni,int yIni);
	virtual void dibujar(Superficie* canvas);
};
