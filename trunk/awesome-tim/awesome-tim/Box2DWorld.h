#pragma once

#include "Box2D/Box2D.h"
#include "Figura.h"
#include "FiguraCompuesta.h"
#include "Constantes.h"
#include "PelotaBasquet.h"
#include "PelotaBowling.h"
#include "GloboHelio.h"
#include "Cuadrado.h"
#include "Triangulo.h"
#include "PlataformaB2ContactListener.h";

class Box2DWorld
{
private:
	PlataformaB2ContactListener* list;
	Box2DWorld(void);
	b2World * mundo;
	float tiempoStep;
	int velIteracion, posIteracion;

	bool activo;

public:
	Box2DWorld(float fuerzaX, float fuerzaY,bool flag);
	void setFrecuenciaActualizacion(float tiempoStep, int velIteracion, int posIteracion);
	void actualizar();
	void actualizar(Figura * figura);
	bool agregarFigura(Figura * figura);
	void cambiarParametros(Figura * figura);
	void eliminarFigura(Figura * figura);
	~Box2DWorld(void);
};
