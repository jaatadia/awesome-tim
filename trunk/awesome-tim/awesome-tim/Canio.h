#pragma once
#include "figura.h"
#include "VistaFigAgrandable.h"

class Canio :
	public Figura
{
private:
	int largo;
public:
	Canio(int largo,double pos_x,double pos_y,double angulo);
	~Canio(void);
	void agrandar();
	void achicar();

	virtual int getTipoDimension();
	virtual int getTipoFigura();

	virtual int getLargo();
	virtual void setLargo(int largoN);
	virtual Figura* clonar();

	virtual bool rotable(){return true;}

};
