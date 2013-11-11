#pragma once
#include "figura.h"
#include "Box2D/Box2D.h"

class PaletaFlipper : public Figura{

private:
	bool is_pushed;
	int sentido; //IZQUIERDA (la q va del lado izq) o DERECHA
	b2Body* b2dCuerpo;
	b2RevoluteJoint* b2dJoint;

public:
	PaletaFlipper(double posX,double posY,int sentido);
	~PaletaFlipper(void);

	Figura* clonar();
	int getTipoFigura();
	int getTipoDimension();
	double getXdeRotacion(); //solo para box2d
	double getYdeRotacion(); //solo para box2d
	double getMaxAng();
	double getMinAng();
	void shift();
	bool estaApretada();
	int getSentido();
	void setBox2dData(b2Body* cuerpo,b2RevoluteJoint* enlace);
	void accionar();
	void desaccionar();

	virtual void interactuar(int accion);
};
