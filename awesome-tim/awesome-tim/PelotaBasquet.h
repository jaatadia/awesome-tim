#ifndef __PELOTABASQUET_H__
#define __PELOTABASQUET_H__

#include "Circulo.h"
#include "Constantes.h"

class PelotaBasquet : public Circulo
{
private:
	PelotaBasquet(void);
public:
	PelotaBasquet(double r,double pos_X,double pos_Y,double angulo);
	~PelotaBasquet(void);

	virtual int getTipoDimension(){return PELOTABASQUET;}
	virtual Dimension * clonar();
};

#endif // __PELOTABASQUET_H__