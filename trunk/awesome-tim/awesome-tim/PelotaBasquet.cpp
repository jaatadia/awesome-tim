
#include "PelotaBasquet.h"

bool PelotaBasquet::choqueConFigura(Figura* fig){

	//envuelvo en un poligono de 50 vertices
	PoligonoRegular* pol = (PoligonoRegular*) dimension->devolverPoligonEnvolvente();

	//me fijo si fig choca con esta dimension (para cada una que tenga en este caso solo 1)
	bool choca = false;
	choca = fig->choqueConDimension(pol);

	delete pol;

	return choca;
};


bool PelotaBasquet::choqueConDimension(Dimension* dim){
	
	//envuelvo en un poligono de 50 vertices
//	PoligonoRegular* polPropio = (PoligonoRegular*) dimension->devolverPoligonEnvolvente();

//	return dim->choqueCon(pol);

	return false;
}
