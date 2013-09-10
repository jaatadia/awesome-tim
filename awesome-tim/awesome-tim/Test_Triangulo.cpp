#include "Test_Triangulo.h"
#include <iostream>

void Test_Triangulo::prueba_triangulo(void){
	bool resultado = true;

	if(!prueba_dentro_del_triangulo())
		std::cout << "Falla en Test Triangulo: el punto no esta adentro del triangulo \n";

	if(!prueba_fuera_del_triangulo())
		std::cout << "Falla en Test Triangulo: el punto no esta afuera del triangulo \n";

	if(!prueba_perimetro())
		std::cout << "Falla en Test Triangulo: el punto pertenece al perimetro y dice que es interno\n";

	if(!prueba_rectangulo_exterior())
		std::cout << "Falla en Test Triangulo: el punto del rectangulo exterior esta adentro del triangulo \n";
}


bool Test_Triangulo::prueba_dentro_del_triangulo(void){

	Posicion* punto1 = new Posicion(0,0);
	Posicion* punto2 = new Posicion(2,0);
	Posicion* punto3 = new Posicion(1,1);

	Triangulo* triangulo = new Triangulo(0,0,0,punto1,punto2,punto3);

	bool pertenece = triangulo->puntoPertenece(1,0.5);

	delete(punto1);
	delete(punto2);
	delete(punto3);
	delete(triangulo);
	return pertenece;
}

bool Test_Triangulo::prueba_fuera_del_triangulo(void){

	Posicion* punto1 = new Posicion(0,0);
	Posicion* punto2 = new Posicion(2,0);
	Posicion* punto3 = new Posicion(1,1);

	Triangulo* triangulo = new Triangulo(0,0,0,punto1,punto2,punto3);

	bool pertenece = (!triangulo->puntoPertenece(4,5));

	delete(punto1);
	delete(punto2);
	delete(punto3);
	delete(triangulo);
	return pertenece;
}

bool Test_Triangulo::prueba_perimetro(void){

	Posicion* punto1 = new Posicion(0,0);
	Posicion* punto2 = new Posicion(2,0);
	Posicion* punto3 = new Posicion(1,1);

	Triangulo* triangulo = new Triangulo(0,0,0,punto1,punto2,punto3);

	bool pertenece = (!triangulo->puntoPertenece(0.5,0.5));

	delete(punto1);
	delete(punto2);
	delete(punto3);
	delete(triangulo);
	return pertenece;
}

bool Test_Triangulo::prueba_rectangulo_exterior(void){

	Posicion* punto1 = new Posicion(0,0);
	Posicion* punto2 = new Posicion(2,0);
	Posicion* punto3 = new Posicion(1,1);

	Triangulo* triangulo = new Triangulo(0,0,0,punto1,punto2,punto3);

	bool pertenece = (!triangulo->puntoPertenece(0.05,0.06));

	delete(punto1);
	delete(punto2);
	delete(punto3);
	delete(triangulo);
	return pertenece;
	
}