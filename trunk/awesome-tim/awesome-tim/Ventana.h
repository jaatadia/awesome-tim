#pragma once

#include "SDL.h"
#include "Superficie.h"
#include "Fallable.h"


#define VENTANA_TAG "Ventana"

/* ejemplo de uso: al crear una creamos una ventana donde imprimir nuestras imagenes por pantalla
	basicamente su uso es el siguiente
	
	Ventana* win = new Ventana();
	if(!win->huboFallos){
		win->dibujar(superficie);
	}
	delete win;

	cada ventana tiene un ID para poder indentificarse, win->getID();

*/


class Ventana: public Fallable
{
private:
	SDL_Window* win;
	SDL_Renderer* ren;

public:
	Ventana(void);//crea una ventana
	~Ventana(void);//destruye la ventana
	int getID();//devuelve el numero de ID de la ventana
	void dibujar(Superficie* sup);//dibuja en la ventana la superficie pasada
	int getAncho();
	int getAlto();
	void resize(int ancho,int alto);
};
