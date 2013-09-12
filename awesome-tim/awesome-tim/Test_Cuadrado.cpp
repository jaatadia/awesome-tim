#include "Test_Cuadrado.h"
#include <iostream>

void Test_Cuadrado::prueba_cuadrado(void){

	bool resultado = true;

	if(!prueba_dentro_del_cuadrado_rotado())
		std::cout << "Falla en Test Cuadrado: el punto no esta adentro del cuadrado \n";

	if(!prueba_fuera_del_cuadrado_rotado())
		std::cout << "Falla en Test Cuadrado: el punto no esta afuera del cuadrado \n";

	if(!prueba_perimetro())
		std::cout << "Falla en Test Cuadrado: el punto pertenece al perimetro y dice que es interno\n";
}


bool Test_Cuadrado::prueba_dentro_del_cuadrado_rotado(void){

	Cuadrado* cuadrado = new Cuadrado(20,20,0,0,45);

	bool res = (cuadrado->puntoPertenece(0,13));

	delete cuadrado;

	return res;
}

bool Test_Cuadrado::prueba_fuera_del_cuadrado_rotado(void){


	Cuadrado* cuadrado = new Cuadrado(20,20,0,0,45);

	bool res = !(cuadrado->puntoPertenece(10,10));

	delete cuadrado;

	return res;

}

bool Test_Cuadrado::prueba_perimetro(void){


	Cuadrado* cuadrado = new Cuadrado(20,20,0,0,0);

	bool res = !(cuadrado->puntoPertenece(10,-5));

	delete cuadrado;

	return res;
}
