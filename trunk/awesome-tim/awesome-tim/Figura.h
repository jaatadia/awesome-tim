#pragma once

#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "Cambiable.h"
#include "VistaFigura.h"
#include "EscalasDeEjes.h"
#include <string>

#include "Box2D/Box2D.h"


class VistaFigura;

class Figura: public Dibujable,public Cambiable
{
public:
	friend class VistaFigura;

protected:
	Figura(){};	
	Dimension* dimension;
	std::string ID;
	VistaFigura* myVista;
	
	b2Body* cuerpo;
	unsigned long int numeroID;

public:
	bool traslucido;

public:
	Figura(const char* ID,Dimension* dim,bool crearVista = true);
	virtual ~Figura(void);

	virtual void cambiarPosicion(double Movx,double Movy);

	virtual bool esMiPosicion(double x,double y);
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual void dibujarEnPixel(Superficie* super);
	virtual void dibujar(Superficie* super);
	virtual void dibujar(Superficie* super,int xIni,int yIni);

	virtual const char* getID();
	virtual int getTipoDimension(){return dimension->getTipoDimension();};
	virtual Dimension* getDimension();
	virtual double getLargo();
	virtual int getTipoFigura(){return -1;};//=0;

	virtual void setTraslucido(bool flag);
	virtual void setAngulo(double angulo);

	virtual void agrandar(){};
	virtual void achicar(){};

	virtual Figura* clonar();//copia la figura

	virtual void setCuerpo(b2Body* cuerpo){
		this->cuerpo = cuerpo;
	}
	virtual b2Body* getCuerpo(){
		return cuerpo;
	}

	virtual void shift(){};
};
