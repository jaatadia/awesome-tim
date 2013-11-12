#include "Fallable.h"

//constructor
Fallable::Fallable()
{
	fallo = false;
}

//devuelve true si se produjo algun fallo
bool Fallable::huboFallos(){
	return fallo;
}

//indica que debe fallar
void Fallable::fallar(){
	fallo = true;
}