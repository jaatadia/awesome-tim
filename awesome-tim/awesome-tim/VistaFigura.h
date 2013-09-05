#pragma once

#include "Imagen.h"
#include "Figura.h"

class Figura;



class VistaFigura{

private:
	Figura* fig;
	Imagen* img;

public:
	VistaFigura(Figura* fig);
	~VistaFigura(void);

	void dibujar(Superficie* canvas);
	void dibujar(Superficie* canvas,double unidadesLogicas);
private:
	void redraw();
};


