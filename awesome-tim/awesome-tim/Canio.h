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
	virtual void getPosPared1(double* x,double* y);
	virtual void getPosPared2(double* x,double* y);

	virtual bool rotable(){return true;}

	virtual void getExtraData(double* d1,double* d2){
		*d1 = largo;
		*d2 = -1;
	}

};
