#pragma once

#include "Figura.h"
# include "Cuadrado.h"
#include "Constantes.h"
#include <math.h>

#include <list>

class FiguraCompuesta :	public Figura{

protected:

	std::list<Figura*> partesFigura;
	std::list<double> angulos; //los angulos iniciales de cada figura componente respecto de su centro local
							   //empieza en cero
	std::list<double> angulosCentroIniciales; //los angulos de cada figura componente respecto del centro del grupo 

	std::list<Figura*>::iterator iterFig;

	//no tiene ID
	//Dimension es un cuadrado
	//no tiene vista 

public:

	/*
	Yo usaria el primer constructor y no el segundo,
	 pero hagan como quieran.
	*/

	/*
	Para usar este:
	1) dim deberia tener el angulo y la posicion de lo que sea el centro, todo el resto a mi no me importa.
	2) En ID puede ir lo que sea no se usa, y no se supone que sea valido pedirla.
	3) En quien herede (en este orden):
		-Poner todas las figuras en la lista partesFigura, ustedes sabran en que posicion estan.
		-Llamar a inicAngulosCentro();
		-En la lista angulos meter los angulos iniciales LOCALES o PROPIOS de cada figura componente en el
		 mismo orden que se metieron en partesFigura.
	*/
	FiguraCompuesta(const char* ID, Dimension* dim);

/*obviamente asumo que todo esta en la posicion correcta como para que encajen las junturas y demas!
  y angulo es el de la figura compuesta.
*/
	FiguraCompuesta( std::list<Figura*> listaFiguras, double angulo );

	virtual ~FiguraCompuesta(void);

	virtual void cambiarPosicion(double Movx,double Movy);
	virtual void setX( double x );
	virtual void setY( double y );

	virtual bool esMiPosicion(double x,double y);
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);

	virtual void dibujarEnPixel(Superficie* super);
	virtual void dibujar(Superficie* super);
	virtual void dibujar(Superficie* super,int xIni,int yIni);

	virtual int getTipoDimension()=0;
	virtual int getTipoFigura()=0;

	virtual void setTraslucido(bool flag);
	virtual void setSuperpuesta(bool flag);

	virtual void setAngulo(double angulo);

	virtual Figura* clonar()=0;//copia la figura

	//para este no devuelve nada valido (vacio)
	virtual const char* getID();

	//para este devuelve un cuadrado con posicion y angulo de la figura
	virtual Dimension* getDimension();

	virtual std::list<Figura*> getFigurasComp(){return partesFigura;};

	//indican si se esta o no chocando con la figura o la dimension en cuestion
	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);

protected:

	void inicAngulosCentro();

//sí, los saque tal cual del terreno, sí, deberian estar en un clase aparte tipo "CosasDeGeometria" y sí pienso hacerlo 
//en algun momento
private:
	double calcularAngulo(Dimension* dim, double XVector1,double YVector1,double XVector2,double YVector2);
	int obtenerCuadranteDeClick(double X, double Y);
	bool anguloEsPositivo(double X1, double Y1, double X2, double Y2);
};
