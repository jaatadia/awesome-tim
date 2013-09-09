#include "Test_Triangulo.h"
#include <iostream>

void Test_Triangulo::prueba_triangulo(void){
	bool resultado = true;

	resultado = prueba_dentro_del_triangulo();
	if(resultado == false){
		std::cout << "Falla en Test Triangulo el punto esta adentro del triangulo \n";
	}

	resultado = prueba_dentro_del_triangulo();
	if(resultado == false){
		std::cout << "Falla en Test Triangulo el punto esta afuera del triangulo \n";
	}
}


bool Test_Triangulo::prueba_dentro_del_triangulo(void){

	Posicion* punto1 = new Posicion(2,3);
	Posicion* punto2 = new Posicion(0,4);
	Posicion* punto3 = new Posicion(3,1);

	Triangulo* triangulo = new Triangulo(0,0,0,punto1,punto2,punto3);

	return (triangulo->puntoPertenece(1.5,3.8));
}

bool Test_Triangulo::prueba_fuera_del_triangulo(void){
	return true;
}