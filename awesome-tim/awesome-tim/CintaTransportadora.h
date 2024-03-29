#pragma once

//#include "Figura.h"
#include "FiguraCompuesta.h"
#include "Cuadrado.h"
#include "Constantes.h"

class CintaTransportadora: public FiguraCompuesta
{
private:
	int largo;
	//double angulo;
	bool atadoDerecha;
	bool atadoIzquierda;
	Figura* cinta;
	Figura* circizq;
	Figura* circder;
	Figura* clavo;
	Figura* clavo2;

private:
	void calcularPosClavo(double angulo,double* posX_clavo,double* posY_clavo);

public:
	//cuidado: hardcodeada la dimension de cuadrado que lo contiene!
	CintaTransportadora(int largo,double pos_x,double pos_y,double angulo);
	~CintaTransportadora(void);
	virtual int getLargo();
	virtual void setLargo(int largoN);
	void agrandar();
	void achicar();

	virtual int getTipoFigura();
	virtual int getTipoDimension();

	virtual Figura* clonar();

	virtual bool esAtableCorrea(){return !(atadoIzquierda || atadoDerecha);};
	virtual void atarCorrea(){
		atadoIzquierda = true;
		atadoDerecha = true;
	};
	virtual void desatarCorrea(){
		atadoIzquierda = false;
		atadoDerecha = false;
	};

	double getRadio(){return RADIO_CINTA_TRANSPORTADORA;};

	virtual void setAngulo(double angulo);

	virtual void getExtraData(double* d1,double* d2){
		*d1 = largo;
		*d2 = -1;
	}

	virtual bool tienePartesRotables(){return true;};
	virtual double getAnguloPartesRotables(){return circizq->getDimension()->getAngulo();};
	virtual void setAnguloPartesRotables(double angulo){this->setAngulo(angulo);};
};
