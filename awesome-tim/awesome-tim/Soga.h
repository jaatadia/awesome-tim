#pragma once
#include "Figura.h"
#include "Cuadrado.h"

#include <math.h>

//NO la puedo agregar al mundo del box2d
//PERO la tengo que agregar a terreno!

//supongo que ahora sera un rectangulo y ya.
//por ahora de 0.3 de alto.

class Soga :public Figura{

private:

	double largoEstirada;
	Figura* extremo1,extremo2;

public:
	//llamar con el ID (de ser posible el de segmento de soga...)
	//no me interesan las dimensiones, hasta null me sirve.
	Soga(const char* ID, Dimension* dim);
	~Soga(void);

public:

	virtual Figura* clonar();//copia la figura

////redefinir el dibujar, que averigue su dimension cada vez...
//	/*	
//	myVista->dibujar(super);
//	setCambio(false);
//	*/
//	void dibujarEnPixel(Superficie* super);
//	void dibujar(Superficie* super);
//	void dibujar(Superficie* super,int xIni, int yIni);

	virtual int getTipoFigura(){return SOGA;}
	virtual int getTipoDimension(){return CUADRADO;}

private:
	//recalcularDimension();
};
