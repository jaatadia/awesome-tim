#pragma once

#include "Cuadrado.h"
#include "Posicion.h"

class Test_Cuadrado
{
public:

	static void prueba_cuadrado(void);

private:
	static bool prueba_dentro_del_cuadrado_rotado(void);
	static bool prueba_fuera_del_cuadrado_rotado(void);
	static bool prueba_perimetro(void);

};