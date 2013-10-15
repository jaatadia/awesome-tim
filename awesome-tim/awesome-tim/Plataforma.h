#pragma once
#include "figura.h"
#include "Cuadrado.h"
#include "VistaFigAgrandable.h"

class Plataforma : public Figura{
private:
	int largo;
public:
	Plataforma(int largo,double pos_x,double pos_y,double angulo);
	~Plataforma(void);
	void agrandar();
	void achicar();

	virtual int getTipoDimension();
	virtual int getTipoFigura();

	virtual int getLargo();
	virtual Figura* clonar();

	virtual bool rotable(){return true;}

//	bool choqueConFigura(Figura* fig);
};
