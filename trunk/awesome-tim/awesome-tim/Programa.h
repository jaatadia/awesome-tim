#pragma once

#include "Ventana.h"
#include "Superficie.h"
#include "Rectangulo.h"

#define PROGRAMA_TAG "Programa"

/* ejemplo de uso
	Programa prog = Programa(file); //se le pasaria la direccion del archivo a cargar desde el argv
	if(!prog->huboFallos()) prog.correr();
*/


class Programa: public Fallable
{
private:
	Ventana* ventana;
	Superficie* superficie;
	bool running;
	Imagen* img;
	Uint16 rot;

public:
	Programa(const char* file);//incia el programa
	~Programa(void);//destruye el programa
	void correr();//empieza a correr el programa
	
private:
	void onEvent();//maneja los eventos
	void onLoop();//actualiza el modelo
	void onRender();//dibuja en la ventana
};
