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
#include "B2ContactListener.h"
#include "Soga.h"
#include "Tijera.h"


class Box2DWorld
{
private:
	B2ContactListener* list;
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

	void eliminarSoga(Soga* figura);

private:
	void ponerEnPolea(Figura* soga, b2Body* cuerpo1,Figura* fig1,int num1,b2Body* cuerpo2,Figura* fig2,int num2);
	void actuarTijera(b2Body* cuerpo, Tijera* fig);
};
