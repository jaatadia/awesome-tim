#pragma once 

#include "SDL.h"
#include "Fallable.h"
#include "Rectangulo.h"
#include "Imagen.h"

#define SUPERFICIE_TAG "Superficie"

/*ejemplo de uso: sirve para dibujar imagenes sobre ella u otras superficies y luego pasar a la ventana para que lo muestre

	superficie->restore(); //se blanquea la superficie
	Imagen* temp = img->scaleImagen(200,200);//se escalea una imagen para dibujarla
	superficie->dibujarImagen(temp,NULL,0,0);//se dibuja en nuestra superficie
	delete temp;//liberamos la memoria
	ventana->dibujar(superficie);//dibujamos en la ventana

*/


class Superficie: public Fallable
{

public:
	friend class Ventana;

private:
	SDL_Surface* superficie;
public:
	Superficie(int ancho,int alto);//nueva superficie de las dimensiones pasadas
	~Superficie(void); //destructor de la superficie

	void setSurface (SDL_Surface* sup){ (*superficie) = (*sup);};
	SDL_Surface* getSurface(){return superficie;}

	void restore();//repinta el fondo de la imagen
	void restoreAlpha();//repinta el fondo de la imagen
	void restoreGris();//repinta el fondo de la imagen
	int getAlto(); //devuelve el alto de la superficie
	int getAncho(); //devuelve el ancho de la superficie
	void setTransparency(Uint8 alpha);//transparenta toda la superficie a lo pedido (0 completamente transparente 255 completamente opaco)
	
	//dibuja en las pocisiones x/yDestino el rectOrigen de sup (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
	void dibujarSupreficie(Superficie* sup,Rectangulo* rectOrigen,int xDestino,int yDestino);
	//dibuja en las pocisiones x/yDestino el rectOrigen de img (rectOrigen pude ser NULL si se desea copiar toda la superficie sup)
	void dibujarImagen(Imagen* img,Rectangulo* rectOrigen,int xDestino,int yDestino);

	void dibujarCuadradoNegro(int x, int y, int ancho,int alto);

	void dibujarLinea(int x1,int y1,int x2, int y2,int ancho);

	Uint32 getPixel(int x,int y );

	//las siguientes devuelve NULL en caso de error
	Superficie* rotarSuperficie(double angulo);//devuelve una copia rotada de la imagen
	Superficie* rotarCuadradoSuperficie(double ang);//devuelve una copia rotada de la imagen manteniendo el tam original
	Superficie* scaleSurface(int pixelesAncho,int pixeleAlto);//resizea la imagen a ancho x alto

private:
	Superficie();
};
