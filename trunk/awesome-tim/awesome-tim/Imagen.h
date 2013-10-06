#pragma once

#include "SDL.h"
#include "Fallable.h"
#include "Rectangulo.h"
#define IMAGEN_TAG "Imagen"

/* ejemplo de uso
	sirve para pasarsela a una superficie para dibujar, por ejemplo cargo una imagen la quiero rotar
	y pasar a una superficie para dibujar en su tamaño original en la posicion 23,23


	notar que implementa fallable!!

	Imagen* img = new Imagen("../images/test.png");
	Imagen* imgRot = imagen->rotarCuadradoImagen(200.4);
	superficie->dibujarImagen(imgRot,NULL,23,23);
	delete img;
	delete imgRot;


*/


class Imagen: public Fallable
{
public:
	friend class Superficie;

private:
	SDL_Surface* superficie;
	Imagen(bool flag);

public:
	Imagen();//crea la imagen default
	Imagen(const char* ruta);//crea una imagen a partir del directorio pasado en caso de no lograrse se pone como fallado
	Imagen(const char* texto,int alto,int r,int g,int b);//crea una imagen a partir del texto pasado
	
		
	~Imagen(void);
	int getAlto(); //devuelve el alto de la imagen
	int getAncho(); //devuelve el ancho de la imagen
	
	void setTransparency(Uint8 alpha);//transparenta toda la imagen a lo pedido (0 completamente transparente 255 completamente opaco)
	
	//las siguientes devuelve NULL en caso de error
	Imagen* rotarImagen(double angulo);//devuelve una copia rotada de la imagen
	Imagen* rotarCuadradoImagen(double ang);//devuelve una copia rotada de la imagen manteniendo el tam original
	Imagen* scaleImagen(int pixelesAncho,int pixelesAlto);//devuelve una copia resizeada de la imagen
	Imagen* rotarZoom(int ancho,int alto,double angulo);//rota y zoomea la img


	Imagen(int ancho,int alto);//nueva superficie de las dimensiones pasadas
	void dibujarImagen(Imagen* img,Rectangulo* rectOrigen,int xDestino,int yDestino);
};
