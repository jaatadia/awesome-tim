#pragma once
#include "FiguraCompuesta.h"
#include "Cuadrado.h"

#include <math.h>

//sera una concatenacion de rectangulos.
//por ahora 1 de largo y 0.3 de ancho para el segmento en general.
//y largo arbitrario para el ultimo.
class Soga :public FiguraCompuesta{

private:

	double largoEstirada;

public:
	//llamar con el ID de un cuadrado/rectangulo (de ser posible el de segmento de soga...)
	//en dimension las de las soga estirada (pasarla como un cuadrado HORIZONTAL, yo creo las nuevas)
	//POR AHORA : Voy a ignorar el ancho que me pasen, digamos que siempre es el mismo.
	Soga(const char* ID, Dimension* dim);

	//hacer otra version con una lista de dimensiones!!

	~Soga(void);

public:
	
	virtual int getTipoDimension(){return SOGA;};

	virtual Figura* clonar();//copia la figura

	const char** getListaDeIDs();
};
