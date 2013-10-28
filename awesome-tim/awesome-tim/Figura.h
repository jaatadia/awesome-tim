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
	
	Figura* fig1;
	Figura* fig2;

	bool es_fija;
	bool interactua_en_play;

	int largoF;

	bool marcada;

public:
	bool traslucido;
	bool superpuesta ;
	VistaFigura* myVista;

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
	virtual int getTipoFigura(){return -1;};//=0;

	virtual void setTraslucido(bool flag);
	virtual void setSuperpuesta(bool flag);

	virtual void setAngulo(double angulo);

	virtual void agrandar(){};
	virtual void achicar(){};

	virtual void interactuar(){};

	virtual Figura* clonar(bool cambiar);//copia la figura
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
	virtual void posFigura1(double* x, double* y){};
	virtual void posFigura2(double* x, double* y){};


	virtual bool esAtableCorrea(){return false;};
	virtual void posAtableCorrea(double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY();
	}
	virtual void atarCorrea(){};
	virtual void desatarCorrea(){};

	bool esFija();
    void fijarFigura();
	bool esInteractuableEnPlay();
	void hacerInteractuableEnPlay();
	
	//se le pasa la poicion en la que esta queriendo atar y devuelve el numero de posicion atable mas cercano(-1 es que no habia)
	virtual int esAtableSoga(double x,double y){return -1;}
	//se le pasa un numero de posicion atable y devuelve la posicion x e y de donde se ata por mas que ya este atado
	virtual void posAtableSoga(int numero,double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY();
	}
	virtual void atarSoga(int numero){};//le dice que ate una soga en su pocicion atable numero
	virtual void desatarSoga(int numero){};//le dice que desate una soga de su posicion atable numero


	//indican si se esta o no chocando con la figura o la dimension en cuestion
	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);

	virtual void setLargo(int largo){this->largoF = largo;};
	virtual int getLargo(){ return largoF;};

	virtual bool cortaSoga(){
		return false;
	}

	virtual bool pinchaGlobo(){
		return false;
	}

	virtual void marcar(bool flag){
		marcada = flag;
	}

	virtual bool estaMarcada(){
		return marcada;
	}
};
