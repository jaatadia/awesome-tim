#pragma once

#include "Figura.h"
#include "Cuadrado.h"
#include "Constantes.h"

class CintaTransportadora: public Figura
{
private:
	double largo;
	double angulo;
public:

	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	CintaTransportadora(double largo,double pos_x,double pos_y,double angulo);
	~CintaTransportadora(void);
	virtual double getLargo();
	void agrandar();
	void achicar();

	virtual int getTipoFigura(){return CINTATRANSPORTADORA;}
	virtual int getTipoDimension(){return CUADRADO;}

	virtual Figura* clonar();

	virtual bool esAtableCorrea(){return true;};

	double getRadio(){return RADIO_CINTA_TRANSPORTADORA;};

	virtual void setAngulo(double angulo);

//	bool choqueConFigura(Figura* fig);
};
