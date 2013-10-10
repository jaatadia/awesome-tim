#pragma once

#include "Posicion.h"
#include "Dibujable.h"
#include "Dimension.h"
#include "PoligonoRegular.h"
#include "Cuadrado.h"
#include "Circulo.h"
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
	Figura* fig1;
	Figura* fig2;

public:
	bool traslucido;

public:
	

	Figura(const char* ID,Dimension* dim,bool crearVista = true);
	virtual ~Figura(void);

	virtual void cambiarPosicion(double Movx,double Movy);
	virtual void setX( double x );
	virtual void setY( double y );

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

	virtual double getRadio(){return dimension->getAncho()/2.0;}
	virtual void shift(){};//cambia los modos de la figura
	virtual bool rotable(){return false;} //devuelve si la figura es rotable
	virtual bool esUnion(){return false;}//devuelve si la figura se trata de una union entre fig1 y fig2
	virtual void desUnir(){};

	virtual void setFigura1(Figura* fig){this->fig1 = fig;};
	virtual void setFigura2(Figura* fig){this->fig2 = fig;};
	virtual Figura* getFigura1(){return fig1;};
	virtual Figura* getFigura2(){return fig2;};
	
	virtual bool esAtableCorrea(){return false;};
	virtual void posAtableCorrea(double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY();
	}
	virtual void atarCorrea(){};
	virtual void desatarCorrea(){};
	
	////devuelve int -1 si no es atable 1, si se ata en la primera union de soga y 2 en la segunda
	//virtual int esAtableSoga(double* x,double* y){
	//	*x = this->getDimension()->getX();
	//	*y = this->getDimension()->getY();
	//	return false;
	//}
	//virtual void setSoga1(Figura* soga){
	//	this->soga1 = soga;
	//}
	//virtual void setSoga2(Figura* soga){
	//	this->soga2 = soga;
	//}
	//virtual Figura* getSoga1(){
	//	return this->soga1;
	//}
	//virtual Figura* getSoga2(){
	//	return this->soga2;
	//}

//indican si se esta o no chocando con la figura o la dimension en cuestion
	virtual bool choqueConFigura(Figura* fig){return false;};

	virtual bool choqueConDimension(PoligonoRegular* pol){return false;};
	virtual bool choqueConDimension(Cuadrado* cuadrado){return false;};
	virtual bool choqueConDimension(Circulo* circ){return false;};
};
