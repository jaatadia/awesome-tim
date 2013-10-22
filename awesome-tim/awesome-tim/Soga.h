#pragma once
#include "Linea.h"
#include <list>

class Soga :public Linea{

private:
	Soga(DLinea* dim);
	std::list<Figura*> segmentos;

public:
	int num1,num2;
	Soga(double x1,double y1,double x2, double y2,double ancho = 1);
	~Soga(void);

public:
	virtual Figura* clonar();//copia la figura
	virtual int getTipoFigura(){return SOGA;}

	virtual void posFigura1(double* x, double* y){fig1->posAtableSoga(num1,x,y);};
	virtual void posFigura2(double* x, double* y){fig2->posAtableSoga(num2,x,y);};

	virtual void setNumsPosAtable(int num1, int num2){
		this->num1 = num1;
		this->num2 = num2;
	}

	virtual void desUnir(){
		fig1->desatarSoga(num1);
		fig2->desatarSoga(num2);
	}
	
	virtual bool choqueConFigura(Figura* fig);

	virtual bool choqueConDimension(Dimension* dim);

	std::list<Figura*> getSegmentos();
	void putSegmento(Figura* fig);
};