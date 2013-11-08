#pragma once
#include "figura.h"

class PaletaFlipper : public Figura{

private:
	bool push;
	int sentido; //IZQUIERDA (la q va del lado izq) o DERECHA
public:
	PaletaFlipper(double posX,double posY,double angulo,int sentido);
	~PaletaFlipper(void);

	Figura* clonar();
	int getTipoFigura();
	int getTipoDimension();
	double getXdeRotacion();
	double getYdeRotacion();


	virtual void interactuar(int accion);
};
